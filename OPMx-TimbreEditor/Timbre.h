#pragma once



#include "FmChip.h"
#include "Value.h"
#include "Intermediate.h"



class CTimbre
{
	public:
		virtual ~CTimbre();
		
		CTimbre(int SampleRate);
		
		IValue& GetValue(int x, int y);
	
	private:
		CDummy Dummy;
		
		struct Control
		{
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			
			CValue<1, 0, 7> ALG;
			CValue<1, 0, 7> FB;
			
			CValue<3, 0, 999> NUM;
			CValue<2, 1, 96> KML;
			CValue<2, 1, 96> KMH;
			
			CValue<1, 0, 3> WF;
			CValue<3, 0, 255> FRQ;
			CValue<1, 0, 3> AMS;
			CValue<3, 0, 127> AMD;
			CValue<1, 0, 7> PMS;
			CValue<3, 0, 127> PMD;
			CValue<1, 0, 1> LFR;
			
			CValue<3, -95, 95> KT;
			CValue<4, -999, 999> FDT;
		};
		Control Control;
		
		struct Operator
		{
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			
			CValue<2, 0, 31> AR;
			CValue<2, 0, 31> D1R;
			CValue<2, 0, 31> D2R;
			CValue<2, 0, 15> RR;
			CValue<2, 0, 15> D1L;
			CValue<3, 0, 127> TL;
			CValue<1, 0, 3> KS;
			CValue<2, 0, 15> MT;
			CValue<1, 0, 7> DT1;
			CValue<1, 0, 3> DT2;
			CValue<1, 0, 1> AME;
		};
		Operator aOperator[4];
		
		int m_Note;
		bool m_bPlay;
		bool m_bKeyOn;
		
		bool m_bFDE;
		bool m_bFDE1;
		bool m_bFDE2;
		bool m_bFDE3;
		bool m_bFDE4;
		
		uint32_t output_rate;
		emulated_time output_step;
		emulated_time output_pos;
		std::unique_ptr<FmChipBase> m_pFmChip;
	
	private:
		void SubmitSourceBuffer(std::vector<int>& aOutput);
		
		void OctNoteFrac(int Note, int RegH, int RegL);
		void KeyOn();
	
	public:
		void Play(int Note);
		void Stop();
		
		void OnBufferStart(std::vector<int>& aOutput);
		
		void SetIntermediate(CIntermediate v);
		CIntermediate GetIntermediate();
};
