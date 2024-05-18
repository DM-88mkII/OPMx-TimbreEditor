


#include "pch.h"
#include <cmath>
#include <random>
#include <memory>
#include "Timbre.h"



CTimbre::~CTimbre()
{
}



CTimbre::CTimbre(int SampleRate)
:m_bPlay(false)
,m_bKeyOn(true)
,output_rate(SampleRate)
,output_step(0x100000000ull / output_rate)
,output_pos(0)
,m_pFmChip(std::make_unique<FmChip<ymfm::ym2151>>(output_rate * 64, EChipType::YM2151))
{
	{	// 
		Control.EN.SetValue(1);
		Control.FDE.SetValue(1);
		Control.ALG.SetValue(0);
		Control.FB.SetValue(0);
		Control.KML.SetValue(1);
		Control.KMH.SetValue(96);
		Control.NUM.SetValue(0);
		Control.KT.SetValue(0);
		Control.DT.SetValue(0);
		
		for (int i = 0; i < 4; ++i){
			aOperator[i].EN.SetValue(1);
			aOperator[i].FDE.SetValue(1);
			
			aOperator[i].AR.SetValue(31);
			aOperator[i].D1R.SetValue(0);
			aOperator[i].D2R.SetValue(0);
			aOperator[i].RR.SetValue(15);
			aOperator[i].D1L.SetValue(0);
			aOperator[i].KS.SetValue(0);
			aOperator[i].MT.SetValue(1);
			aOperator[i].DT1.SetValue(0);
			aOperator[i].DT2.SetValue(0);
			aOperator[i].AME.SetValue(0);
		}
		aOperator[0].TL.SetValue(36);
		aOperator[1].TL.SetValue(36);
		aOperator[2].TL.SetValue(36);
		aOperator[3].TL.SetValue(0);
	}
}



IValue& CTimbre::GetValue(int x, int y)
{
	switch (y){
		case 0:{
			switch (x){
				case 0: return Control.EN;
				case 1: return Control.FDE;
				case 2: return Control.ALG;
				case 3: return Control.FB;
				case 4: return Control.KML;
				case 5: return Control.KMH;
				case 6: return Control.WF;
				case 7: return Control.FRQ;
				case 8: return Control.AMS;
				case 9: return Control.AMD;
				case 10: return Control.PMS;
				case 11: return Control.PMD;
				case 12: return Control.NUM;
				case 13: return Control.KT;
				case 14: return Control.DT;
			}
			break;
		}
		default:{
			switch (x){
				case 0: return aOperator[y-1].EN;
				case 1: return aOperator[y-1].FDE;
				case 2: return aOperator[y-1].AR;
				case 3: return aOperator[y-1].D1R;
				case 4: return aOperator[y-1].D2R;
				case 5: return aOperator[y-1].RR;
				case 6: return aOperator[y-1].D1L;
				case 7: return aOperator[y-1].TL;
				case 8: return aOperator[y-1].KS;
				case 9: return aOperator[y-1].MT;
				case 10: return aOperator[y-1].DT1;
				case 11: return aOperator[y-1].DT2;
				case 12: return aOperator[y-1].AME;
				case 13: break;
				case 14: break;
			}
			break;
		}
	}
	return Dummy;
}



void CTimbre::OnBufferStart(std::vector<int>& aOutput)
{
	SubmitSourceBuffer(aOutput);
	KeyOn();
}



void CTimbre::SubmitSourceBuffer(std::vector<int>& aOutput)
{
	for (auto& i : aOutput){
		int32_t outputs[1] = {0};
		m_pFmChip->generate(output_pos, output_step, outputs);
		i += outputs[0];
		
		output_pos += output_step;
	}
}



static const int16_t s_aOctNoteFrac[]={
//	c       c+      d       d+      e       f       f+      g       g+      a       a+      b
	0x0000, 0x0000, 0x0100, 0x0200, 0x0400, 0x0500, 0x0600, 0x0800, 0x0900, 0x0a00, 0x0c00, 0x0d00,	// o1
	0x0e00, 0x1000, 0x1100, 0x1200, 0x1400, 0x1500, 0x1600, 0x1800, 0x1900, 0x1a00, 0x1c00, 0x1d00,	// o2
	0x1e00, 0x2000, 0x2100, 0x2200, 0x2400, 0x2500, 0x2600, 0x2800, 0x2900, 0x2a00, 0x2c00, 0x2d00,	// o3
	0x2e00, 0x3000, 0x3100, 0x3200, 0x3400, 0x3500, 0x3600, 0x3800, 0x3900, 0x3a00, 0x3c00, 0x3d00,	// o4
	0x3e00, 0x4000, 0x4100, 0x4200, 0x4400, 0x4500, 0x4600, 0x4800, 0x4900, 0x4a00, 0x4c00, 0x4d00,	// o5
	0x4e00, 0x5000, 0x5100, 0x5200, 0x5400, 0x5500, 0x5600, 0x5800, 0x5900, 0x5a00, 0x5c00, 0x5d00,	// o6
	0x5e00, 0x6000, 0x6100, 0x6200, 0x6400, 0x6500, 0x6600, 0x6800, 0x6900, 0x6a00, 0x6c00, 0x6d00,	// o7
	0x6e00, 0x7000, 0x7100, 0x7200, 0x7400, 0x7500, 0x7600, 0x7800, 0x7900, 0x7a00, 0x7c00, 0x7d00,	// o8
	0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00, 0x7e00,	// o9
};

void CTimbre::OctNoteFrac(int Note, int RegH, int RegL)
{
	Note += Control.KT.GetValue();
	Note += (Control.DT.GetValue()>>6);
	Note = (Note >= 0)? Note: 0;
	Note = (int)((Note < std::size(s_aOctNoteFrac))? Note: std::size(s_aOctNoteFrac)-1);
	
	auto OctNoteFrac = s_aOctNoteFrac[Note];
	OctNoteFrac += ((Control.DT.GetValue()&0x3f)<<2);
	
	m_pFmChip->write(RegH, OctNoteFrac>>8);
	m_pFmChip->write(RegL, OctNoteFrac&0xff);
}



void CTimbre::KeyOn()
{
	if (m_bPlay && !m_bKeyOn){
		m_bKeyOn = true;
		m_pFmChip->write(0x40, ((aOperator[0].DT1.GetValue()<<4) | aOperator[0].MT.GetValue()));
		m_pFmChip->write(0x50, ((aOperator[1].DT1.GetValue()<<4) | aOperator[1].MT.GetValue()));
		m_pFmChip->write(0x48, ((aOperator[2].DT1.GetValue()<<4) | aOperator[2].MT.GetValue()));
		m_pFmChip->write(0x58, ((aOperator[3].DT1.GetValue()<<4) | aOperator[3].MT.GetValue()));
		m_pFmChip->write(0x60, aOperator[0].TL.GetValue());
		m_pFmChip->write(0x70, aOperator[1].TL.GetValue());
		m_pFmChip->write(0x68, aOperator[2].TL.GetValue());
		m_pFmChip->write(0x78, aOperator[3].TL.GetValue());
		m_pFmChip->write(0x80, ((aOperator[0].KS.GetValue()<<6) | aOperator[0].AR.GetValue()));
		m_pFmChip->write(0x90, ((aOperator[1].KS.GetValue()<<6) | aOperator[1].AR.GetValue()));
		m_pFmChip->write(0x88, ((aOperator[2].KS.GetValue()<<6) | aOperator[2].AR.GetValue()));
		m_pFmChip->write(0x98, ((aOperator[3].KS.GetValue()<<6) | aOperator[3].AR.GetValue()));
		m_pFmChip->write(0xa0, ((aOperator[0].AME.GetValue()<<7) | aOperator[0].D1R.GetValue()));
		m_pFmChip->write(0xb0, ((aOperator[1].AME.GetValue()<<7) | aOperator[1].D1R.GetValue()));
		m_pFmChip->write(0xa8, ((aOperator[2].AME.GetValue()<<7) | aOperator[2].D1R.GetValue()));
		m_pFmChip->write(0xb8, ((aOperator[3].AME.GetValue()<<7) | aOperator[3].D1R.GetValue()));
		m_pFmChip->write(0xc0, ((aOperator[0].DT2.GetValue()<<6) | aOperator[0].D2R.GetValue()));
		m_pFmChip->write(0xd0, ((aOperator[1].DT2.GetValue()<<6) | aOperator[1].D2R.GetValue()));
		m_pFmChip->write(0xc8, ((aOperator[2].DT2.GetValue()<<6) | aOperator[2].D2R.GetValue()));
		m_pFmChip->write(0xd8, ((aOperator[3].DT2.GetValue()<<6) | aOperator[3].D2R.GetValue()));
		m_pFmChip->write(0xe0, ((aOperator[0].D1L.GetValue()<<4) | aOperator[0].RR.GetValue()));
		m_pFmChip->write(0xf0, ((aOperator[1].D1L.GetValue()<<4) | aOperator[1].RR.GetValue()));
		m_pFmChip->write(0xe8, ((aOperator[2].D1L.GetValue()<<4) | aOperator[2].RR.GetValue()));
		m_pFmChip->write(0xf8, ((aOperator[3].D1L.GetValue()<<4) | aOperator[3].RR.GetValue()));
		m_pFmChip->write(0x20, (0xc0 | (Control.FB.GetValue()<<3) | Control.ALG.GetValue()));
		
		m_pFmChip->write(0x01, 0x02);
		m_pFmChip->write(0x01, 0x00);
		m_pFmChip->write(0x18, Control.FRQ.GetValue());
		m_pFmChip->write(0x19, (0x00 | Control.AMD.GetValue()));
		m_pFmChip->write(0x19, (0x80 | Control.PMD.GetValue()));
		m_pFmChip->write(0x1b, Control.WF.GetValue());
		m_pFmChip->write(0x38, ((Control.PMS.GetValue()<<4) | Control.AMS.GetValue()));
		
		{	// 
			OctNoteFrac(m_Note, 0x28, 0x30);
		}
		
		if (m_Note >= Control.KML.GetValue() && m_Note <= Control.KMH.GetValue()){
			uint8_t KeyOn = 0;
			KeyOn |= (aOperator[0].EN.GetValue()<<3);
			KeyOn |= (aOperator[1].EN.GetValue()<<4);
			KeyOn |= (aOperator[2].EN.GetValue()<<5);
			KeyOn |= (aOperator[3].EN.GetValue()<<6);
			KeyOn = (Control.EN.GetValue() == 0)? 0: KeyOn;
			m_pFmChip->write(0x08, KeyOn);
		}
	}
}



void CTimbre::Play(int Note)
{
	if (!m_bPlay){
		m_Note = Note;
		
		m_bPlay = true;
		m_bKeyOn = false;
		
		m_bFDE = Control.FDE.GetValue();
		m_bFDE1 = (bool)aOperator[0].FDE.GetValue() && m_bFDE;
		m_bFDE2 = (bool)aOperator[1].FDE.GetValue() && m_bFDE;
		m_bFDE3 = (bool)aOperator[2].FDE.GetValue() && m_bFDE;
		m_bFDE4 = (bool)aOperator[3].FDE.GetValue() && m_bFDE;
		
		if (m_bFDE1) m_pFmChip->write(0xe0, ((aOperator[0].D1L.GetValue()<<4) | /*RR*/15));
		if (m_bFDE2) m_pFmChip->write(0xf0, ((aOperator[1].D1L.GetValue()<<4) | /*RR*/15));
		if (m_bFDE3) m_pFmChip->write(0xe8, ((aOperator[2].D1L.GetValue()<<4) | /*RR*/15));
		if (m_bFDE4) m_pFmChip->write(0xf8, ((aOperator[3].D1L.GetValue()<<4) | /*RR*/15));
	}
}
void CTimbre::Stop()
{
	if (m_bPlay){
		m_bPlay = false;
		m_pFmChip->write(0x08, 0x00);
	}
}



void CTimbre::SetIntermediate(CIntermediate v)
{
	Control.EN.SetValue(v.Control.EN);
	Control.FDE.SetValue(v.Control.FDE);
	Control.ALG.SetValue(v.Control.ALG);
	Control.FB.SetValue(v.Control.FB);
	Control.KML.SetValue(v.Control.KML);
	Control.KMH.SetValue(v.Control.KMH);
	Control.WF.SetValue(v.Control.WF);
	Control.FRQ.SetValue(v.Control.FRQ);
	Control.AMS.SetValue(v.Control.AMS);
	Control.AMD.SetValue(v.Control.AMD);
	Control.PMS.SetValue(v.Control.PMS);
	Control.PMD.SetValue(v.Control.PMD);
	Control.NUM.SetValue(v.Control.NUM);
	Control.KT.SetValue(v.Control.KT);
	Control.DT.SetValue(v.Control.DT);
	
	for (int i = 0; i < 4; ++i){
		aOperator[i].EN.SetValue(v.aOperator[i].EN);
		aOperator[i].FDE.SetValue(v.aOperator[i].FDE);
		aOperator[i].AR.SetValue(v.aOperator[i].AR);
		aOperator[i].D1R.SetValue(v.aOperator[i].D1R);
		aOperator[i].D2R.SetValue(v.aOperator[i].D2R);
		aOperator[i].RR.SetValue(v.aOperator[i].RR);
		aOperator[i].D1L.SetValue(v.aOperator[i].D1L);
		aOperator[i].TL.SetValue(v.aOperator[i].TL);
		aOperator[i].KS.SetValue(v.aOperator[i].KS);
		aOperator[i].MT.SetValue(v.aOperator[i].MT);
		aOperator[i].DT1.SetValue(v.aOperator[i].DT1);
		aOperator[i].DT2.SetValue(v.aOperator[i].DT2);
		aOperator[i].AME.SetValue(v.aOperator[i].AME);
	}
}



CIntermediate CTimbre::GetIntermediate()
{
	CIntermediate v;
	
	v.Control.EN = Control.EN.GetValue();
	v.Control.FDE = Control.FDE.GetValue();
	v.Control.ALG = Control.ALG.GetValue();
	v.Control.FB = Control.FB.GetValue();
	v.Control.KML = Control.KML.GetValue();
	v.Control.KMH = Control.KMH.GetValue();
	v.Control.WF = Control.WF.GetValue();
	v.Control.FRQ = Control.FRQ.GetValue();
	v.Control.AMS = Control.AMS.GetValue();
	v.Control.AMD = Control.AMD.GetValue();
	v.Control.PMS = Control.PMS.GetValue();
	v.Control.PMD = Control.PMD.GetValue();
	v.Control.NUM = Control.NUM.GetValue();
	v.Control.KT = Control.KT.GetValue();
	v.Control.DT = Control.DT.GetValue();
	
	for (int i = 0; i < 4; ++i){
		v.aOperator[i].EN = aOperator[i].EN.GetValue();
		v.aOperator[i].FDE = aOperator[i].FDE.GetValue();
		v.aOperator[i].AR = aOperator[i].AR.GetValue();
		v.aOperator[i].D1R = aOperator[i].D1R.GetValue();
		v.aOperator[i].D2R = aOperator[i].D2R.GetValue();
		v.aOperator[i].RR = aOperator[i].RR.GetValue();
		v.aOperator[i].D1L = aOperator[i].D1L.GetValue();
		v.aOperator[i].TL = aOperator[i].TL.GetValue();
		v.aOperator[i].KS = aOperator[i].KS.GetValue();
		v.aOperator[i].MT = aOperator[i].MT.GetValue();
		v.aOperator[i].DT1 = aOperator[i].DT1.GetValue();
		v.aOperator[i].DT2 = aOperator[i].DT2.GetValue();
		v.aOperator[i].AME = aOperator[i].AME.GetValue();
	}
	
	return std::move(v);
}
