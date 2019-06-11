#include "Game/App/App.hpp"

#include "Engine/Core/WindowsLean.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Game/App/AppCommon.hpp"

#include "Engine/Rendering/Window.hpp"
#include "Engine/Core/Blackboard.hpp"


#include "Engine/Rendering/LowLevel/RHIInstance.hpp"
#include "Engine/Rendering/LowLevel/RHIDevice.hpp"
#include "Engine/Rendering/LowLevel/RHIOutput.hpp"
#include "Engine/Rendering/LowLevel/DepthStencilState.hpp"
#include "Engine/Rendering/LowLevel/BlendState.hpp"
#include "Engine/Rendering/LowLevel/RasterizerState.hpp"
#include "Engine/Rendering/LowLevel/ShaderProgram.hpp"
#include "Engine/Rendering/LowLevel/ShaderProgramStage.hpp"
#include "Engine/Rendering/LowLevel/ConstantBuffer.hpp"
#include "Engine/Rendering/LowLevel/FrameBuffer.hpp"
#include "Engine/Rendering/LowLevel/VertexBuffer.hpp"
#include "Engine/Rendering/LowLevel/IndexBuffer.hpp"
#include "Engine/Rendering/LowLevel/VertexTypes.hpp"
#include "Engine/Rendering/LowLevel/Sampler.hpp"
#include "Engine/Rendering/HighLevel/Image.hpp"
#include "Engine/Rendering/LowLevel/Texture2D.hpp"
#include "Engine/Rendering/LowLevel/ShaderResourceView.hpp"
struct CCB
{
	vec4 color;
};
// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void App::Initialize()
{
	// Initialize for subsystems
	InitializeRequiredEngineSubsystems();

	g_theBlackboard = new Blackboard();
	g_theBlackboard->PopulateFromXML("Data/Config.xml");

	g_theWindow = new Window();
	g_theWindow->Initialize(g_theBlackboard->GetValue("Window.AppName", "Main Window"), g_theBlackboard->GetValue("Window.Resolution.Width", 100), g_theBlackboard->GetValue("Window.Resolution.Height", 100));
	g_theWindow->RegisterMemberCallback(this, &App::HandleXOut);

	
	// Rendering Test
	g_theInstance = new RHIInstance();
	g_theInstance->Initialize();

	g_theDevice = new RHIDevice();
	g_theDevice->Initialize(g_theInstance, g_theInstance->GetVideoCard(0));

	g_theOutput = new RHIOutput();
	g_theOutput->Initialize(g_theInstance, g_theDevice, g_theWindow);

}


void App::Destroy()
{
	// Rendering Test
	g_theOutput->Destroy();
	delete g_theOutput;
	g_theOutput = nullptr;

	g_theDevice->Destroy();
	delete g_theDevice;
	g_theDevice = nullptr;

	g_theInstance->Destroy();
	delete g_theInstance;
	g_theInstance = nullptr;


	// Destroy for subsystems
	g_theWindow->Destroy();
	delete g_theWindow;
	g_theWindow = nullptr;

	DestroyRequiredEngineSubsystems();
}



// -----------------------------------------------------------------
// Update
// -----------------------------------------------------------------
void App::RunInternalLoop()
{
	while(!IsQuitting())
	{
		RunFrame();
	}
}


void App::RunFrame()
{
	// BeginFrame for subsystems

	RunMessagePump();
	Update();
	Render();
	

	// EndFrame for subsystems
}


void App::RunMessagePump()
{
	MSG queuedMessage;
	for (;;)
	{
		BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage); // Calls the WndProc
	}
}


void App::Update()
{

}


void App::Render() const
{
	// Render for subsystems



	// Rendering test
	DepthStateDescription dsd;
	dsd.writeDepth = false;
	DepthStencilState* depthStencilState = new DepthStencilState(g_theDevice, DepthStateDescription(), StencilStateDescription());
	BlendStateDescription bsd;
	bsd.colorSrcFactor = BLEND_FACTOR_SOURCE_COLOR;
	bsd.alphaSrcFactor = BLEND_FACTOR_SOURCE_ALPHA;
	BlendState* blendState = new BlendState(g_theDevice, bsd);
	RasterizerStateDescription rsd;
	rsd.cullMode = CULL_BACK;
	RasterizerState* rasterizerState = new RasterizerState(g_theDevice, rsd);
	ShaderProgram* shaderProgram = new ShaderProgram(g_theDevice);
	shaderProgram->LoadFromFiles("Data/Assets/Shaders/test.vs", "", "", "", "Data/Assets/Shaders/test.fs", "");
	FrameBuffer* framebuffer = new FrameBuffer(g_theDevice);
	framebuffer->SetRenderTarget(0, g_theOutput->GetBackBufferRTV());

	Vertex_PCU verts[] = 
	{
		Vertex_PCU(vec3(-1,-1,0), rgba(1,0,0), vec2(0,0)),
		Vertex_PCU(vec3( 1,-1,0), rgba(0,1,0), vec2(1,0)),
		Vertex_PCU(vec3( 1, 1,0), rgba(0,0,1), vec2(1,1)),

		Vertex_PCU(vec3(-1,-1,0), rgba(1,0,0), vec2(0,0)),
		Vertex_PCU(vec3( 1, 1,0), rgba(0,0,1), vec2(1,1)),
		Vertex_PCU(vec3(-1, 1,0), rgba(0,0,1), vec2(0,1))
	};
	VertexBufferDescription vbd;
	vbd.usage = BUFFER_USAGE_IMMUTABLE;
	vbd.elementCount = sizeof(verts) / sizeof(Vertex_PCU);
	vbd.elementSizeBytes = sizeof(Vertex_PCU);
	vbd.allowStreamOut = false;
	VertexBuffer* vertexBuffer = new VertexBuffer(g_theDevice, vbd, verts);

	uint indices[] = 
	{
		0,1,2,
		3,4,5
	};
	IndexBufferDescription ibd;
	ibd.usage = BUFFER_USAGE_IMMUTABLE;
	ibd.elementCount = sizeof(indices) / sizeof(uint);
	ibd.elementSizeBytes = sizeof(uint);
	IndexBuffer* indexBuffer = new IndexBuffer(g_theDevice, ibd, indices);

	
	CCB ccb;
	ccb.color = vec4(1,1,0,1);
	ConstantBuffer* cb = new ConstantBuffer(g_theDevice);
	cb->SetCPUBuffer(&ccb, sizeof(ccb));

	Texture2DDescription texDesc;
	texDesc.dimensions = ivec2(10, 10);
	texDesc.format = TEXTURE_FORMAT_RGBA8;
	texDesc.generateMips = false;
	uchar* texelData = LoadTexelData_Uchar("Data/testRGBA.png", texDesc.dimensions.x, texDesc.dimensions.y, false);
	Texture2D* tex = new Texture2D(g_theDevice, texDesc);
	tex->Update(texelData);
	
	ShaderResourceView* srv = new ShaderResourceView(g_theDevice, tex);

	SamplerDescription samplerDesc;
	samplerDesc.isLinear = false;
	Sampler* sampler = new Sampler(g_theDevice, samplerDesc);

	g_theDevice->BindFrameBuffer(framebuffer);

	// IA
	g_theDevice->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TRIANGLES);
	g_theDevice->BindVertexLayout(Vertex_PCU::GetLayout());
	g_theDevice->BindVertexBuffer(vertexBuffer);
	g_theDevice->BindIndexBuffer(indexBuffer);

	// Prog
	g_theDevice->BindShaderProgram(shaderProgram);
	g_theDevice->BindConstantBuffer(1, cb);
	g_theDevice->BindShaderResourceView(1, srv);
	g_theDevice->BindSampler(1, sampler);

	// RS
	g_theDevice->BindRasterizerState(rasterizerState);
	g_theDevice->SetViewport(vec2(0.0f, 0.0f), vec2(g_theWindow->GetDimensions()), (float)g_theWindow->GetDimensions().y);

	// OM
	g_theDevice->BindDepthStencilState(depthStencilState);
	g_theDevice->BindBlendState(blendState);

	// Evoc
	g_theDevice->DrawIndexed(ibd.elementCount, 0);

	// Flip
	g_theOutput->Present();


	delete sampler;
	delete srv;
	delete tex;
	delete texelData;
	delete cb;
	delete indexBuffer;
	delete vertexBuffer;
	delete framebuffer;
	delete shaderProgram;
	delete depthStencilState;
	delete blendState;
	delete rasterizerState;
}



// -----------------------------------------------------------------
// Quit
// -----------------------------------------------------------------
void App::Quit()
{
	m_isQuitting = true;
}


bool App::IsQuitting() const
{
	return m_isQuitting;
}



// -----------------------------------------------------------------
// Window Callbacks
// -----------------------------------------------------------------
void App::HandleXOut(uint msg, ulonglong wparam, longlong lparam)
{
	UNUSED(wparam);
	UNUSED(lparam);

	if (msg == WM_CLOSE)
	{
		Quit();
	}
}