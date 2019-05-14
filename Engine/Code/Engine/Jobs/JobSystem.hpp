#pragma once

#include <vector>
#include <string>

#include "Engine/Core/Types.hpp"
#include "Engine/Async/Mutex.hpp"

class JobWorkerThread;



class Job
{
public:
	Job(uint flags, int type = -1);
	virtual ~Job() {}

	virtual void Execute() = 0;
	virtual void Finish() {};

	int			 GetUID() const		{ return m_uid; };
	uint		 GetFlags() const	{ return m_flags; };
	int			 GetType() const	{ return m_type; };



private:
	static int GetNextUID();

	int		m_uid	= -1;
	uint	m_flags = 0xffffffff;
	int		m_type;
};



class JobSystem
{
public:
	friend void WorkerThreadUpdateLoop(void* data);

	JobSystem();
	~JobSystem();

	void EndFrame();

	// Worker Thread Creation
	void CreateWorkerThread(const std::string& name, uint flags);
	void DestroyWorkerThread(const std::string& name);

	// Job Queuing
	void QueueJob(Job* job);

	// Job Claiming
	void FinishCompletedJobs();
	void FinishJob(int uid);

	// Job Status Queries
	bool IsJobComplete(int jobUID) const;
	int	 GetNumPendingJobsOfType(int type) const;
	int	 GetNumInProgressJobsOfType(int type) const;
	int	 GetNumCompletedJobsOfType(int type) const;



private:
	// Worker API
	Job* GetJob(uint flags);
	void NotifyJobComplete(Job* job);


	// Workers
	std::vector<JobWorkerThread*>	m_workerThreads;


	// Jobs we plan on processing
	std::vector<Job*>				m_pendingJobs;
	mutable Mutex					m_pendingMutex;

	std::vector<Job*>				m_inProgressJobs;
	mutable Mutex					m_inProgressMutex;

	std::vector<Job*>				m_completedJobs;
	mutable Mutex					m_completedMutex;
};