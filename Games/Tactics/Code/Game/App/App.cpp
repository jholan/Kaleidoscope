#include "Game/App/App.hpp"

#include "Engine/Core/WindowsLean.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/Blackboard.hpp"

#include "Engine/Events/EventSystem.hpp"

#include "Engine/Jobs/JobSystem.hpp"

#include "Engine/Time/Clock.hpp"

#include "Engine/Rendering/Window.hpp"

#include "Game/App/AppCommon.hpp"

#include "Game/Rendering/Mesh.hpp"

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
#include "Engine/3rdParty/IMGUI/imgui.h"
#include "Engine/3rdParty/IMGUI/imgui_impl_win32.h"
#include "Engine/3rdParty/IMGUI/imgui_impl_dx11.h"
#include <XInput.h>
#include "Game/Rendering/Mesh.hpp"
struct CCB
{
	vec4 color;
};
void ImguiInputHandler(uint messageCode, ulonglong wparam, longlong lparam)
{
	HWND hwnd = (HWND)g_theWindow->GetHandle();

	if (ImGui::GetCurrentContext() == NULL)
		return;

	ImGuiIO& io = ImGui::GetIO();
	switch (messageCode)
	{
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
	case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
	{
		int button = 0;
		if (messageCode == WM_LBUTTONDOWN || messageCode == WM_LBUTTONDBLCLK) { button = 0; }
		if (messageCode == WM_RBUTTONDOWN || messageCode == WM_RBUTTONDBLCLK) { button = 1; }
		if (messageCode == WM_MBUTTONDOWN || messageCode == WM_MBUTTONDBLCLK) { button = 2; }
		if (messageCode == WM_XBUTTONDOWN || messageCode == WM_XBUTTONDBLCLK) { button = (	(wparam) == XBUTTON1) ? 3 : 4; }
		if (!ImGui::IsAnyMouseDown() && GetCapture() == NULL)
		{
			SetCapture(hwnd);
		}
		io.MouseDown[button] = true;
		return;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_XBUTTONUP:
	{
		int button = 0;
		if (messageCode == WM_LBUTTONUP) { button = 0; }
		if (messageCode == WM_RBUTTONUP) { button = 1; }
		if (messageCode == WM_MBUTTONUP) { button = 2; }
		if (messageCode == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wparam) == XBUTTON1) ? 3 : 4; }
		io.MouseDown[button] = false;
		if (!ImGui::IsAnyMouseDown() && GetCapture() == hwnd)
		{
			ReleaseCapture();
		}
		return;
	}
	case WM_MOUSEWHEEL:
		io.MouseWheel += (float)GET_WHEEL_DELTA_WPARAM(wparam) / (float)WHEEL_DELTA;
		return;
	case WM_MOUSEHWHEEL:
		io.MouseWheelH += (float)GET_WHEEL_DELTA_WPARAM(wparam) / (float)WHEEL_DELTA;
		return;
	}

	return;
}
// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
void App::Initialize()
{
	// Initialize for subsystems
	InitializeRequiredEngineSubsystems();

	g_theJobSystem->CreateWorkerThread("Resource Loading Thread", 0xffffffff);

	g_theBlackboard = new Blackboard();
	g_theBlackboard->PopulateFromXML("Data/Config.xml");

	g_theWindow = new Window();
	g_theWindow->Initialize(g_theBlackboard->GetValue("Window.AppName", "Main Window"), g_theBlackboard->GetValue("Window.Resolution.Width", 100), g_theBlackboard->GetValue("Window.Resolution.Height", 100));
	g_theWindow->RegisterMemberCallback(this, &App::HandleXOut);
	g_theWindow->RegisterCallback(ImguiInputHandler);

	
	// Rendering Test
	g_theInstance = new RHIInstance();
	g_theInstance->Initialize();

	g_theDevice = new RHIDevice();
	g_theDevice->Initialize(g_theInstance, g_theInstance->GetVideoCard(0));

	g_theOutput = new RHIOutput();
	g_theOutput->Initialize(g_theInstance, g_theDevice, g_theWindow);




	Mesh::LoadDatabaseFile("Data/Databases/Meshes/MeshDummy.xml");
	Mesh::Get("Cerberus");
	//Mesh::Get("Sponza");


	//// Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGui_ImplWin32_Init(g_theWindow->GetHandle());
	//ImGui_ImplDX11_Init(g_theDevice->GetD3D11Device(), g_theDevice->GetD3D11DeviceContext());
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


	//// Imgui Test
	//ImGui_ImplDX11_Shutdown();
	//ImGui_ImplWin32_Shutdown();
	//ImGui::DestroyContext();


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
	++g_theFrameNumber;
	g_theMasterClock->BeginFrame();


	RunMessagePump();
	Update();
	Render();
	

	// EndFrame for subsystems
	Mesh::EndFrame();
	g_theMasterClock->EndFrame();
	g_theJobSystem->EndFrame();
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

bool infoPaneOpen = false;
void RenderTest()
{
	// -----------------------------------------------------------------------------------------------------------------
	// Rendering test --------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------
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
	if (texelData != nullptr)
	{
		tex->Update(texelData);
	}

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
enum eItemType
{
	ITEM_TYPE_STAFF = 0,
	ITEM_TYPE_BOW,
	ITEM_TYPE_SWORD,
	ITEM_TYPE_CONSUMABLE,

	ITEM_TYPE_COUNT
};
std::string GetItemTypeName(eItemType type)
{
	std::string name;

	switch(type)
	{
	case ITEM_TYPE_STAFF:
		name = "Staff";
		break;
	case ITEM_TYPE_BOW:
		name = "Bow";
		break;
	case ITEM_TYPE_SWORD:
		name = "Sword";
		break;
	case ITEM_TYPE_CONSUMABLE:
		name = "Consumable";
		break;
	case ITEM_TYPE_COUNT:
		name = "Count";
		break;
	default:
		break;
	}

	return name;
}
class Item
{
public:
	Item(const std::string& _name, eItemType _type, uint _price) : name(_name), type(_type), price(_price) {};

	std::string name;
	eItemType type;
	uint price;
};
bool itemPanes[ITEM_TYPE_COUNT + 1] = {false, false, false, false, true};
void UpdateItemPaneVisiblity(uint index, bool wasButtonPressed)
{
	if (wasButtonPressed)
	{
		itemPanes[index] != itemPanes[index];
	}
}

std::vector<Item> shopItems = 
{
	Item("Bow1", ITEM_TYPE_BOW, 300),
	Item("Bow2", ITEM_TYPE_BOW, 400),
	Item("Bow3", ITEM_TYPE_BOW, 500),
	Item("Bow4", ITEM_TYPE_BOW, 600),
	Item("Bow5", ITEM_TYPE_BOW, 700),

	Item("Sword1", ITEM_TYPE_SWORD, 300),
	Item("Sword2", ITEM_TYPE_SWORD, 400),
	Item("Sword3", ITEM_TYPE_SWORD, 500),
	Item("Sword4", ITEM_TYPE_SWORD, 600),
	Item("Sword5", ITEM_TYPE_SWORD, 700),

	Item("Staff1", ITEM_TYPE_SWORD, 300),
	Item("Staff2", ITEM_TYPE_SWORD, 400),
	Item("Staff3", ITEM_TYPE_SWORD, 500),
	Item("Staff5", ITEM_TYPE_SWORD, 700),
	Item("Staff4", ITEM_TYPE_SWORD, 600),

	Item("Consumable1", ITEM_TYPE_CONSUMABLE, 300),
	Item("Consumable2", ITEM_TYPE_CONSUMABLE, 400),
	Item("Consumable3", ITEM_TYPE_CONSUMABLE, 500),
	Item("Consumable5", ITEM_TYPE_CONSUMABLE, 700),
	Item("Consumable4", ITEM_TYPE_CONSUMABLE, 600),
};
std::vector<Item> GetItemsWithType(const std::vector<Item>& items, eItemType type)
{
	std::vector<Item> itemsOfType;

	for (int i = 0; i < (int)items.size(); ++i)
	{
		if (items[i].type == type)
		{
			itemsOfType.push_back(items[i]);
		}
	}

	return itemsOfType;
}
void ItemList(const std::vector<Item>& items)
{
			//ImGui::Columns(2, 0, true);
	for (int c = 0; c < 10; ++c)
	{
		for (int i = 0; i < (int)items.size(); ++i)
		{
			ImGui::Selectable("##"); ImGui::SameLine();
				ImGui::Text("%s", items[i].name.c_str()); ImGui::SameLine();
			//ImGui::NextColumn();
				ImGui::Text("%s", GetItemTypeName(items[i].type).c_str()); ImGui::SameLine();
			//ImGui::NextColumn();
				ImGui::Text("%u", items[i].price);
		}
	}
}
void ImguiTest()
{
	// Item Lists
	std::vector<Item> bows = GetItemsWithType(shopItems, ITEM_TYPE_BOW);
	std::vector<Item> staffs = GetItemsWithType(shopItems, ITEM_TYPE_STAFF);
	std::vector<Item> swords = GetItemsWithType(shopItems, ITEM_TYPE_SWORD);
	std::vector<Item> consumables = GetItemsWithType(shopItems, ITEM_TYPE_CONSUMABLE);

	// -----------------------------------------------------------------------------------------------------------------
	// IMGUI Test ------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------
	ImVec2 wd = ImVec2(g_theWindow->GetDimensions().x, g_theWindow->GetDimensions().y);

	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::SetNextWindowSize(wd);
	ImGui::Begin("Canvas", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs);

	// Overview
	ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::SetNextWindowSize(ImVec2(wd.x, wd.y * .1f));
	ImGui::Begin("Overview", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::Columns(2,0,false);
	ImGui::SetColumnWidth(-1, 100);
	ImGui::Image(0, ImVec2(100,100));
	ImGui::NextColumn();
	ImGui::Text("Shop Keepers Name");
	ImGui::Text("Welcome to the shop!");
	ImGui::End();

	// Panel Selector
	ImGui::SetNextWindowPos(ImVec2(0, wd.y * .1f));
	ImGui::SetNextWindowSize(ImVec2(wd.x * 0.5f, wd.y * .1f));
	ImGui::Begin("Panel Selector", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImVec2 buttonDim = ImVec2(100,64);

	ImGui::Columns(ITEM_TYPE_COUNT + 1,0,false);
	UpdateItemPaneVisiblity(ITEM_TYPE_COUNT, ImGui::Button("All", buttonDim));
	ImGui::NextColumn();
	UpdateItemPaneVisiblity(ITEM_TYPE_STAFF, ImGui::Button("Staff", buttonDim));
	ImGui::NextColumn();
	UpdateItemPaneVisiblity(ITEM_TYPE_BOW, ImGui::Button("Bow", buttonDim));
	ImGui::NextColumn();
	UpdateItemPaneVisiblity(ITEM_TYPE_SWORD, ImGui::Button("Sword", buttonDim));
	ImGui::NextColumn();
	UpdateItemPaneVisiblity(ITEM_TYPE_CONSUMABLE, ImGui::Button("Consumable", buttonDim));
	ImGui::NextColumn();
	ImGui::End();

	// Info panel show/ hide
	ImGui::SetNextWindowPos(ImVec2(wd.x * .5f, wd.y * .1f));
	ImGui::SetNextWindowSize(ImVec2(wd.x * .5f, wd.y * .1f));
	ImGui::Begin("Show/ Hide", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	bool changed = ImGui::Button("Show/ Hide Button");
	if(changed) { infoPaneOpen = !infoPaneOpen; }
	ImGui::End();

	// Item list
	ImGui::SetNextWindowPos(ImVec2(0, wd.y * .2f));
	ImGui::SetNextWindowSize(ImVec2(wd.x * 0.5f, wd.y * .8f));
	ImGui::Begin("Item List", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ItemList(shopItems);
	ImGui::End();

	// Info panel
	if (infoPaneOpen)
	{
		ImGui::SetNextWindowPos(ImVec2(wd.x * .5f, wd.y * .2f));
		ImGui::SetNextWindowSize(ImVec2(wd.x * 0.5f, wd.y * .8f));
		ImGui::Begin("Info Panel", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::End();
	}


	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
void App::Render() const
{
	// Render for subsystems
	RenderTest();

	//ImguiTest();
	


	








	// -----------------------------------------------------------------------------------------------------------------
	// Present ---------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------
	g_theOutput->Present();
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