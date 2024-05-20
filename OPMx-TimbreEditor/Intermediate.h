#pragma once



#include "SettingTab.h"



struct CIntermediate
{
	public:
		virtual ~CIntermediate() = default;
		
		CIntermediate();
	
	public:
		struct Control
		{
			int EN;
			int FDE;
			
			int ALG;
			int FB;
			
			int NUM;
			int KML;
			int KMH;
			
			int WF;
			int FRQ;
			int AMS;
			int AMD;
			int PMS;
			int PMD;
			int LFR;
			
			int KT;
			int DT;
		};
		Control Control;
		
		struct Operator
		{
			int EN;
			int FDE;
			
			int AR;
			int D1R;
			int D2R;
			int RR;
			int D1L;
			int TL;
			int KS;
			int MT;
			int DT1;
			int DT2;
			int AME;
		};
		Operator aOperator[4];
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
		
		void ToFormat(CSettingTab::EFormatType EFormatType, CString& Text);
		void FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text);
	
	private:
		void Replace(std::string& source, const std::string& target, const std::string& replace);
		std::vector<std::string> GetLines(const CString& Text);
		std::vector<std::string> GetToken(const std::string& Line, char delim);
		std::string Trim(const std::string& Token, const std::string& trim);
		int ToValue(const std::string& Token);
		void GetOperator(const std::vector<std::string>& Tokens, int iOperator);
		void GetOperatorOPN(const std::vector<std::string>& Tokens, int iOperator);
		
		void ToMucom(CString& Text);
		void FromMucom(const CString& Text);
		
		void ToPmdOPN(CString& Text);
		void FromPmdOPN(const CString& Text);
		
		void ToPmdOPM(CString& Text);
		void FromPmdOPM(const CString& Text);
		
		void ToFmpF(CString& Text);
		void FromFmpF(const CString& Text);
		
		void ToFmpFA(CString& Text);
		void FromFmpFA(const CString& Text);
		
		void ToFmpFC(CString& Text);
		void FromFmpFC(const CString& Text);
		
		void ToMml2VgmF(CString& Text);
		void FromMml2VgmF(const CString& Text);
		
		void ToMml2VgmN(CString& Text);
		void FromMml2VgmN(const CString& Text);
		
		void ToMml2VgmM(CString& Text);
		void FromMml2VgmM(const CString& Text);
		
		void ToMucomDotNET(CString& Text);
		void FromMucomDotNET(const CString& Text);
		
		void ToMAmidiMemoMOPN(CString& Text);
		void FromMAmidiMemoMOPN(const CString& Text);
		
		void ToMAmidiMemoMOPM(CString& Text);
		void FromMAmidiMemoMOPM(const CString& Text);
		
		void ToZMusic(CString& Text);
		void FromZMusic(const CString& Text);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
