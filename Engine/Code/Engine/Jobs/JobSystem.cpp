#include "Engine/Jobs/JobSystem.hpp"

#include "Engine/Core/WindowsLean.hpp"
#include "Engine/Core/BitSet.hpp"

#include "Engine/Async/Thread.hpp"



// -----------------------------------------------------------------
// Job Worker Thread
// -----------------------------------------------------------------
class JobWorkerThread
{
public:
	JobWorkerThread(JobSystem* owner, const std::string& name, uint flags);
	~JobWorkerThread();

	JobSystem*			GetOwner() const						{ return m_owner; };
	uint				GetFlags() const						{ return m_flags; };
	const std::string&	GetName() const							{ return m_name; };

	void				SetActivityState(bool state)			{ m_isActive = state; if(m_isActive == true){m_canBeDestroyed = false;} };
	bool				IsActive() const						{ return m_isActive; };
	bool				CanBeDeleted() const					{ return m_canBeDestroyed; };

	void				SetThreadHandle(ThreadHandle handle)	{ m_handle = handle; };



private:
	std::string		m_name;
	uint			m_flags;
	ThreadHandle	m_handle;
	bool			m_isActive = true;
	bool			m_canBeDestroyed = false;

	JobSystem*		m_owner;
};


void WorkerThreadUpdateLoop(void* data)
{
	JobWorkerThread*	worker = (JobWorkerThread*)data;
	uint				workerFlags = worker->GetFlags();
	JobSystem*			jobDispatch = worker->GetOwner();

	while(worker->IsActive())
	{
		Job* job = jobDispatch->GetJob(workerFlags);
		if (job != nullptr)
		{
			job->Execute();
			jobDispatch->NotifyJobComplete(job);
		}
	}
}



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
JobWorkerThread::JobWorkerThread(JobSystem* owner, const std::string& name, uint flags)
	: m_owner(owner)
	, m_name(name)
	, m_flags(flags)
{

}


JobWorkerThread::~JobWorkerThread()
{

}




// -----------------------------------------------------------------
// Job Base Class
// -----------------------------------------------------------------
Job::Job(uint flags, int type)
	: m_flags(flags)
	, m_type(type)
	, m_uid(GetNextUID())
{
	
}


static int nextUID = 0;
int Job::GetNextUID()
{
	int uid = nextUID;
	++nextUID;

	return uid;
}



// -----------------------------------------------------------------
// Job System
// Composition
// -----------------------------------------------------------------
JobSystem::JobSystem()
{

}


JobSystem::~JobSystem()
{

}


void JobSystem::EndFrame()
{
	// Check for deletable workers
	for (int i = m_workerThreads.size() - 1; i >= 0; --i)
	{
		if (m_workerThreads[i]->CanBeDeleted())
		{
			m_workerThreads.erase(m_workerThreads.begin() + i);
		}
	}


	FinishCompletedJobs();
}



// -----------------------------------------------------------------
// Worker Thread Creation
// -----------------------------------------------------------------
void JobSystem::CreateWorkerThread(const std::string& name, uint flags)
{
	// Create the worker thread and cache a reference
	JobWorkerThread* worker = new JobWorkerThread(this, name, flags);
	m_workerThreads.push_back(worker);


	// Spin up the actual thread
	ThreadHandle handle = Thread_Create(WorkerThreadUpdateLoop, (void*)worker);
	worker->SetThreadHandle(handle);
}


void JobSystem::DestroyWorkerThread(const std::string& name)
{
	for (int i = 0; i < (int)m_workerThreads.size(); ++i)
	{
		JobWorkerThread* worker = m_workerThreads[i];
		if (worker->GetName() == name)
		{
			worker->SetActivityState(false);
		}
	}
}



// -----------------------------------------------------------------
// Job Queuing
// -----------------------------------------------------------------
void JobSystem::QueueJob(Job* job)
{
	m_pendingMutex.Lock();

	// Critical Section
	m_pendingJobs.push_back(job);

	m_pendingMutex.Unlock();
}



// -----------------------------------------------------------------
// Job Claiming
// -----------------------------------------------------------------
void JobSystem::FinishCompletedJobs()
{
	std::vector<Job*> completedJobs;


	m_completedMutex.Lock();

	// Critical Section
	// Copy and clear the list of completed jobs so we can still complete jobs while we spin the callbacks
	completedJobs = m_completedJobs;
	m_completedJobs.clear();

	m_completedMutex.Unlock();


	// Finish all 
	for (int i = 0; i < (int)completedJobs.size(); ++i)
	{
		Job* job = completedJobs[i];
		job->Finish();
	}
}


void JobSystem::FinishJob(int uid)
{
	Job* job = nullptr;

	// Wait for the job to be completed
	while(IsJobComplete(uid) == false)
	{
		Thread_YieldTimeSlice();
	}


	m_completedMutex.Lock();

	// Critical Section
	// Grab the job
	for (int i = 0; i < (int)m_completedJobs.size(); ++i)
	{
		if (m_completedJobs[i]->GetUID() == uid)
		{
			// Remove it from the list so we dont stall the completion lock
			job = m_completedJobs[i];
			m_completedJobs.erase(m_completedJobs.begin() + i);
			break;
		}
	}

	m_completedMutex.Unlock();


	if (job != nullptr)
	{
		job->Finish();
	}
}



// -----------------------------------------------------------------
// Job Status Queries
// -----------------------------------------------------------------
bool JobSystem::IsJobComplete(int jobUID) const
{
	bool isComplete = false;


	m_completedMutex.Lock();

	// Critical Section
	for (int i = 0; i < (int)m_completedJobs.size(); ++i)
	{
		if (m_completedJobs[i]->GetUID() == jobUID)
		{
			isComplete = true;
			break;
		}
	}

	m_completedMutex.Unlock();


	return isComplete;
}


int JobSystem::GetNumPendingJobsOfType(int type) const
{
	int numJobs = 0;


	m_pendingMutex.Lock();

	// Critical Section
	for (int i = 0; i < (int)m_pendingJobs.size(); ++i)
	{
		if (m_pendingJobs[i]->GetType() == type)
		{
			++numJobs;
		}
	}

	m_pendingMutex.Unlock();


	return numJobs;
}


int JobSystem::GetNumInProgressJobsOfType(int type) const
{
	int numJobs = 0;


	m_inProgressMutex.Lock();

	// Critical Section
	for (int i = 0; i < (int)m_inProgressJobs.size(); ++i)
	{
		if (m_inProgressJobs[i]->GetType() == type)
		{
			++numJobs;
		}
	}

	m_inProgressMutex.Unlock();


	return numJobs;
}


int JobSystem::GetNumCompletedJobsOfType(int type) const
{
	int numJobs = 0;


	m_completedMutex.Lock();

	// Critical Section
	for (int i = 0; i < (int)m_completedJobs.size(); ++i)
	{
		if (m_completedJobs[i]->GetType() == type)
		{
			++numJobs;
		}
	}

	m_completedMutex.Unlock();


	return numJobs;
}



// -----------------------------------------------------------------
// Worker API
// -----------------------------------------------------------------
Job* JobSystem::GetJob(uint flags)
{
	Job* job = nullptr;

	m_pendingMutex.Lock();
	m_inProgressMutex.Lock();


	// Critical Section
	// Grab a job if we can
	for (int i = 0; i < (int)m_pendingJobs.size(); ++i)
	{
		// Check to see if our flags are compatible with any jobs
		Job* testJob = m_pendingJobs[i];
		if (AreBitsSet(testJob->GetFlags(), flags) == true)
		{
			// If it is grab the job and remove it from the pending list
			job = testJob;
			m_pendingJobs.erase(m_pendingJobs.begin() + i);
			break;
		}
	}

	// If we got a job add it to the pending list
	if (job != nullptr)
	{
		m_pendingJobs.push_back(job);
	}


	m_inProgressMutex.Unlock();
	m_pendingMutex.Unlock();

	return job;
}


void JobSystem::NotifyJobComplete(Job* job)
{
	// GOD job != nullptr


	m_pendingMutex.Lock();
	m_completedMutex.Lock();


	// Critical Section
	// Find the job in the list of pending jobs and remove it
	bool wasPending = false;
	for (int i = 0; i < (int)m_pendingJobs.size(); ++i)
	{
		if (m_pendingJobs[i] == job)
		{
			wasPending = true;
			m_pendingJobs.erase(m_pendingJobs.begin() + i);
		}
	}

	// If it was a pending job add it to the list of completed jobs
	if (wasPending)
	{
		m_completedJobs.push_back(job);
	}


	m_completedMutex.Unlock();
	m_pendingMutex.Unlock();
}