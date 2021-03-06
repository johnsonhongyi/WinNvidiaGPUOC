// NVIDIA_GPU_OC.cpp : Defines the entry point for the console application.
// Created by Josh Stephenson 


#include "WinNvidiaGPUOC.h"
#include <iostream>

namespace NV_API 
{
	OC_API::OC_API()
	{
		m_hModule = LoadLibraryA("NVGPU_DLL.dll");
		if (m_hModule == nullptr) {
			std::cout << "Error loading: 'NVGPU_API.dll'...\n";
			throw(0xFF);
		}

		char* fnNameArray[10] = { nullptr };
		fnNameArray[0] = new char[12] { "InitGPU_API" };
		fnNameArray[1] = new char[18] { "Set_GPU_OVERCLOCK" };
		fnNameArray[2] = new char[11] { "Set_CoreOC" };
		fnNameArray[3] = new char[10] { "Set_MEMOC" };
		fnNameArray[4] = new char[13] { "CloseGPU_API" };
		fnNameArray[5] = new char[24] { "Get_GPU_Overclock_range" };
		fnNameArray[6] = new char[22] { "Get_GPU_Overclock_Max" };
		fnNameArray[7] = new char[15] { "Set_GPU_Number" };
		fnNameArray[8] = new char[17] { "Get_VFPointFile" };
		fnNameArray[9] = new char[13] { "Set_VFOffset" };
		

		for (int i = 0; i < 10; ++i) { fnPtrArray[i] = GetProcAddress(m_hModule, fnNameArray[i]); }

		for (int i = 0; i < 10; ++i) 
		{
			if (fnPtrArray[i] == nullptr) {
				std::cout << "Error loading: 'NVGPU_API.dll'...\n";
				throw(0xFF);
			}
		}

		m_InitGPU_API();

		for (int i = 0; i < 10; ++i) { delete[] fnNameArray[i]; }
	}

	int OC_API::m_InitGPU_API()
	{
		int(_stdcall* fn)() = (int(_stdcall*)())fnPtrArray[0];
		return fn();
	}

	int OC_API::Set_GPU_OVERCLOCK(bool E_Over, int OC_GPU, int OC_M, int OC_V) 
	{
		int(_stdcall* fn)(bool _E_Over, int _OC_GPU, int _OC_M, int _OC_V) = (int(_stdcall*)(bool _E_Over, int _OC_GPU, int _OC_M, int _OC_V))fnPtrArray[1];
		return fn(E_Over, OC_GPU, OC_M, OC_V);
	}

	int OC_API::Set_CoreOC(int index, int offset) 
	{
		int(_stdcall* fn)(int _index, int _offset) = (int(_stdcall*)(int _index, int _offset))fnPtrArray[2];
		return fn(index, offset);
	}

	int OC_API::Set_MEMOC(int index, int offset) 
	{
		int(_stdcall* fn)(int _index, int _offset) = (int(_stdcall*)(int _index, int _offset))fnPtrArray[3];
		return fn(index, offset);
	}

	void OC_API::m_CloseGPU_API() 
	{
		void(_stdcall* fn)() = (void(_stdcall*)())fnPtrArray[4];
		fn();
	}

	int OC_API::Get_GPU_Overclock_range() 
	{
		int(_stdcall* fn)() = (int(_stdcall*)())fnPtrArray[5];
		return fn();
	}

	int OC_API::Get_GPU_Overclock_Max() 
	{
		int(_stdcall* fn)() = (int(_stdcall*)())fnPtrArray[6];
		return fn();
	}

	int OC_API::Set_GPU_Number(int number) 
	{
		int(_stdcall* fn)(int _number) = (int(_stdcall*)(int _number))fnPtrArray[7];
		return fn(number);
	}

	void* OC_API::Read_VF_Point(const char* file_name) 
	{
		void*(_stdcall* fn)(const char* file_name) = (void*(_stdcall*)(const char* file_name))fnPtrArray[8];
		return fn(file_name);
	}

	void OC_API::Set_VFOffset(int number, int vfPointIdx, int freqOffsetkHz) 
	{
		void(_stdcall* fn)(int _number, int _vfPointIdx, int _freqOffsetkHz) = (void (_stdcall*)(int number, int vfPointIdx, int freqOffsetkHz))fnPtrArray[9];
		fn(number, vfPointIdx, freqOffsetkHz);
	}

	void OC_API::reset()
	{
		Set_CoreOC(0, 0);
		Set_MEMOC(0, 0);
	}

	OC_API::~OC_API() 
	{
		m_CloseGPU_API();
		FreeLibrary(m_hModule); 
	}

}

using namespace NV_API;

int main()
{
	std::cout << "Overclocking your system...\n";
	OC_API api;
	api.Set_CoreOC(0, 155);
	api.Set_MEMOC(0, 0);
	getchar();
    return 0;
}

