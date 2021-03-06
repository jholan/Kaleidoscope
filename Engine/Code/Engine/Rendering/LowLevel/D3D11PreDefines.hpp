#pragma once



// RHI
struct IDXGIFactory;
struct IDXGIAdapter;
struct IDXGISwapChain;

struct DXGI_ADAPTER_DESC;

struct ID3DUserDefinedAnnotation;


// Device
struct ID3D11Device;
struct ID3D11DeviceContext;


// Fixed Function State
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;
struct ID3D11BlendState;  


// Shader Stages
struct ID3D11DeviceChild;
struct ID3D11VertexShader;
struct ID3D11HullShader;
struct ID3D11DomainShader;
struct ID3D11GeometryShader;
struct ID3D11PixelShader;
struct ID3D11ComputeShader;


// Input Layout
struct ID3D11InputLayout;


// GPUBuffer
struct ID3D11Buffer;


// Texture
struct ID3D11Resource;
struct ID3D11Texture2D;

enum	DXGI_FORMAT;


// View
struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11UnorderedAccessView;


// Sampler
struct ID3D11SamplerState;


// Enums
enum D3D11_BLEND_OP;
enum D3D11_BLEND;
enum D3D11_CULL_MODE;
enum D3D11_FILL_MODE;
enum D3D11_COMPARISON_FUNC;
enum D3D11_STENCIL_OP;
enum D3D11_USAGE;
enum D3D11_BIND_FLAG;
enum D3D11_TEXTURE_ADDRESS_MODE;
enum D3D_PRIMITIVE_TOPOLOGY;