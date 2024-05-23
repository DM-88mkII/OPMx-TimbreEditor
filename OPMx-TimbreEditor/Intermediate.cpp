﻿


#include "pch.h"
#include "Intermediate.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>



CIntermediate::CIntermediate()
:Control{0}
,aOperator{0}
{
	Control.EN = 1;
	Control.FDE = 1;
	Control.KML = 1;
	Control.KMH = 96;
	
	for (int i = 0; i < _countof(aOperator); ++i){
		aOperator[i].EN = 1;
		aOperator[i].FDE = 1;
	}
}



void CIntermediate::to_json(nlohmann::json& j) const
{
	j = nlohmann::json{
		{"Information",{
			{"Summary",		"Timbre for OPM Series",	},
			{"ChipType",	"YM2151",	},
		}},
		{"Meta",{
			{"Application",	"OPMx-TimbreEditor",	},
			{"Version",		"0.0.0",	},
		}},
		{"Timbre",{
			{"Control",{
				{"EN",		Control.EN,	},
				{"FDE",		Control.FDE,},
				{"ALG",		Control.ALG,},
				{"FB",		Control.FB,	},
				{"NUM",		Control.NUM,},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
				{"WF",		Control.WF,	},
				{"FRQ",		Control.FRQ,},
				{"AMS",		Control.AMS,},
				{"AMD",		Control.AMD,},
				{"PMS",		Control.PMS,},
				{"PMD",		Control.PMD,},
				{"LFR",		Control.LFR,},
				{"KT",		Control.KT,	},
				{"FDT",		Control.FDT,},
			}},
			{"Operators",{
				{"EN",{		aOperator[0].EN,	aOperator[1].EN,	aOperator[2].EN,	aOperator[3].EN,	}},
				{"FDE",{	aOperator[0].FDE,	aOperator[1].FDE,	aOperator[2].FDE,	aOperator[3].FDE,	}},
				{"AR",{		aOperator[0].AR,	aOperator[1].AR,	aOperator[2].AR,	aOperator[3].AR,	}},
				{"D1R",{	aOperator[0].D1R,	aOperator[1].D1R,	aOperator[2].D1R,	aOperator[3].D1R,	}},
				{"D2R",{	aOperator[0].D2R,	aOperator[1].D2R,	aOperator[2].D2R,	aOperator[3].D2R,	}},
				{"RR",{		aOperator[0].RR,	aOperator[1].RR,	aOperator[2].RR,	aOperator[3].RR,	}},
				{"D1L",{	aOperator[0].D1L,	aOperator[1].D1L,	aOperator[2].D1L,	aOperator[3].D1L,	}},
				{"TL",{		aOperator[0].TL,	aOperator[1].TL,	aOperator[2].TL,	aOperator[3].TL,	}},
				{"KS",{		aOperator[0].KS,	aOperator[1].KS,	aOperator[2].KS,	aOperator[3].KS,	}},
				{"MT",{		aOperator[0].MT,	aOperator[1].MT,	aOperator[2].MT,	aOperator[3].MT,	}},
				{"DT1",{	aOperator[0].DT1,	aOperator[1].DT1,	aOperator[2].DT1,	aOperator[3].DT1,	}},
				{"DT2",{	aOperator[0].DT2,	aOperator[1].DT2,	aOperator[2].DT2,	aOperator[3].DT2,	}},
				{"AME",{	aOperator[0].AME,	aOperator[1].AME,	aOperator[2].AME,	aOperator[3].AME,	}},
			}},
		}},
	};
}



void CIntermediate::from_json(const nlohmann::json& j)
{
	std::exception_ptr pException;
	try {
		{	// 
			auto Information = j.at("Information");
			auto Application = Information.at("Summary").get<std::string>();
			auto ChipType = Information.at("ChipType").get<std::string>();
		}
		
		{	// 
			auto Meta = j.at("Meta");
			auto Application = Meta.at("Application").get<std::string>();
			auto Version = Meta.at("Version").get<std::string>();
		}
		
		{	// 
			auto Timbre = j.at("Timbre");
			
			{	// 
				auto o = Timbre.at("Control");
				Control.EN = o.at("EN").get<int>();
				Control.FDE = o.at("FDE").get<int>();
				Control.ALG = o.at("ALG").get<int>();
				Control.FB = o.at("FB").get<int>();
				Control.NUM = o.at("NUM").get<int>();
				Control.KML = o.value("KML", 0);
				Control.KMH = o.value("KMH", 128);
				Control.WF = o.at("WF").get<int>();
				Control.FRQ = o.at("FRQ").get<int>();
				Control.AMS = o.at("AMS").get<int>();
				Control.AMD = o.at("AMD").get<int>();
				Control.PMS = o.at("PMS").get<int>();
				Control.PMD = o.at("PMD").get<int>();
				Control.LFR = o.value("LFR", 0);
				Control.KT = o.at("KT").get<int>();
				Control.FDT = o.value("FDT", 0);
			}
			
			{	// 
				auto SetOperator = [this](nlohmann::json& Timbre, int i)
				{
					aOperator[i].EN = Timbre.at("EN").at(i).get<int>();
					aOperator[i].FDE = Timbre.at("FDE").at(i).get<int>();
					aOperator[i].AR = Timbre.at("AR").at(i).get<int>();
					aOperator[i].D1R = Timbre.at("D1R").at(i).get<int>();
					aOperator[i].D2R = Timbre.at("D2R").at(i).get<int>();
					aOperator[i].RR = Timbre.at("RR").at(i).get<int>();
					aOperator[i].D1L = Timbre.at("D1L").at(i).get<int>();
					aOperator[i].TL = Timbre.at("TL").at(i).get<int>();
					aOperator[i].KS = Timbre.at("KS").at(i).get<int>();
					aOperator[i].MT = Timbre.at("MT").at(i).get<int>();
					aOperator[i].DT1 = Timbre.at("DT1").at(i).get<int>();
					aOperator[i].DT2 = Timbre.at("DT2").at(i).get<int>();
					aOperator[i].AME = Timbre.at("AME").at(i).get<int>();
				};
				
				auto o = Timbre.at("Operators");
				for (int i = 0; i < _countof(aOperator); ++i) SetOperator(o, i);
			}
		}
	}
	catch (...)
	{
		pException = std::current_exception();
	}
	if (pException){
		std::rethrow_exception(pException);
	}
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }



void CIntermediate::ToFormat(CSettingTab::EFormatType EFormatType, CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::Mucom:{			ToMucom(Text);			break;	}
		case CSettingTab::EFormatType::PmdOPN:{			ToPmdOPN(Text);			break;	}
		case CSettingTab::EFormatType::PmdOPM:{			ToPmdOPM(Text);			break;	}
		case CSettingTab::EFormatType::Fmp:{			ToFmp(Text);			break;	}
		case CSettingTab::EFormatType::FmpA:{			ToFmpA(Text);			break;	}
		case CSettingTab::EFormatType::Fmp7F:{			ToFmp7F(Text);			break;	}
		case CSettingTab::EFormatType::Fmp7FA:{			ToFmp7FA(Text);			break;	}
		case CSettingTab::EFormatType::Fmp7FC:{			ToFmp7FC(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmF:{		ToMml2VgmF(Text);		break;	}
		case CSettingTab::EFormatType::Mml2VgmN:{		ToMml2VgmN(Text);		break;	}
		case CSettingTab::EFormatType::Mml2VgmM:{		ToMml2VgmM(Text);		break;	}
		case CSettingTab::EFormatType::mucomDotNET:{	ToMucomDotNET(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPN:{	ToMAmidiMemoMOPN(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPM:{	ToMAmidiMemoMOPM(Text);	break;	}
		case CSettingTab::EFormatType::ZMusicV:{		ToZMusicV(Text);		break;	}
		case CSettingTab::EFormatType::ZMusicAt:{		ToZMusicAt(Text);		break;	}
		case CSettingTab::EFormatType::NagDrv:{			ToNagDrv(Text);			break;	}
		case CSettingTab::EFormatType::NrtDrv:{			ToNrtDrv(Text);			break;	}
		case CSettingTab::EFormatType::N88Basic:{		ToN88Basic(Text);		break;	}
	}
}



void CIntermediate::FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::Mucom:{			FromMucom(Text);			break;	}
		case CSettingTab::EFormatType::PmdOPN:{			FromPmdOPN(Text);			break;	}
		case CSettingTab::EFormatType::PmdOPM:{			FromPmdOPM(Text);			break;	}
		case CSettingTab::EFormatType::Fmp:{			FromFmp(Text);				break;	}
		case CSettingTab::EFormatType::FmpA:{			FromFmpA(Text);				break;	}
		case CSettingTab::EFormatType::Fmp7F:{			FromFmp7F(Text);			break;	}
		case CSettingTab::EFormatType::Fmp7FA:{			FromFmp7FA(Text);			break;	}
		case CSettingTab::EFormatType::Fmp7FC:{			FromFmp7FC(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmF:{		FromMml2VgmF(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmN:{		FromMml2VgmN(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmM:{		FromMml2VgmM(Text);			break;	}
		case CSettingTab::EFormatType::mucomDotNET:{	FromMucomDotNET(Text);		break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPN:{	FromMAmidiMemoMOPN(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPM:{	FromMAmidiMemoMOPM(Text);	break;	}
		case CSettingTab::EFormatType::ZMusicV:{		FromZMusicV(Text);			break;	}
		case CSettingTab::EFormatType::ZMusicAt:{		FromZMusicAt(Text);			break;	}
		case CSettingTab::EFormatType::NagDrv:{			FromNagDrv(Text);			break;	}
		case CSettingTab::EFormatType::NrtDrv:{			FromNrtDrv(Text);			break;	}
		case CSettingTab::EFormatType::N88Basic:{		FromN88Basic(Text);			break;	}
	}
}



void CIntermediate::Replace(std::string& source, const std::string& target, const std::string& replace)
{
	while (true){
		size_t p = 0;
		size_t o = 0;
		size_t n = target.length();
		int c = 0;
		while ((p = source.find(target, o)) != std::string::npos){
			source.replace(p, n, replace);
			o = p + replace.length();
			++c;
		}
		if (c == 0) break;
	}
}


std::vector<std::string> CIntermediate::GetLines(const CString& Text)
{
	std::string s = CStringA(Text).GetBuffer();
	Replace(s, "\r\n", "\n");
	
	std::stringstream ss(s);
	std::string Line;
	std::vector<std::string> Lines;
	while (std::getline(ss, Line, '\n')) Lines.push_back(Line);
	return Lines;
}



std::vector<std::string> CIntermediate::GetToken(const std::string& Line, char delim)
{
	std::stringstream ss(Line);
	std::string Token;
	std::vector<std::string> Tokens;
	while (std::getline(ss, Token, delim)) Tokens.push_back(Token);
	return Tokens;
}



std::string CIntermediate::CommentCut(const std::string& Line, const std::string& target)
{
	auto First = Line.find(target);
	if (First != std::string::npos){
		return Line.substr(0, First);
	} else {
		return Line;
	}
}



std::string CIntermediate::Trim(const std::string& Token, const std::string& trim)
{
	std::string Result;
	auto First = Token.find_first_not_of(trim);
	if (First != std::string::npos){
		auto Last = Token.find_last_not_of(trim);
		Result = Token.substr(First, Last - First + 1);
	}
	return Result;
}



int CIntermediate::ToValue(const std::string& Token)
{
	auto Value = Trim(Token, " ");
	return (Value.empty() || (Value.find_first_of("0123456789") == std::string::npos))? 0: std::stoi(Value);
}



void CIntermediate::GetOperatorOPN(const std::vector<std::string>& Tokens, int iOperator)
{
	int TimbreToken = 0;
	for (auto Token : Tokens){
		switch (TimbreToken){
			case 0:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
			case 1:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
			case 2:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
			case 3:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
			case 4:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
			case 5:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
			case 6:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
			case 7:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
			case 8:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
		}
		++TimbreToken;
	}
}



void CIntermediate::GetOperatorOPM(const std::vector<std::string>& Tokens, int iOperator)
{
	int TimbreToken = 0;
	for (auto Token : Tokens){
		switch (TimbreToken){
			case 0:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
			case 1:{	aOperator[iOperator].D1R = ToValue(Token);	break;	}
			case 2:{	aOperator[iOperator].D2R = ToValue(Token);	break;	}
			case 3:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
			case 4:{	aOperator[iOperator].D1L = ToValue(Token);	break;	}
			case 5:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
			case 6:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
			case 7:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
			case 8:{	aOperator[iOperator].DT1 = ToValue(Token);	break;	}
			case 9:{	aOperator[iOperator].DT2 = ToValue(Token);	break;	}
			case 10:{	aOperator[iOperator].AME = ToValue(Token);	break;	}
		}
		++TimbreToken;
	}
}



void CIntermediate::ToMucom(CString& Text)
{
	std::string s;
	s += std::format("  @{}:", Control.NUM);
	s += "{\n";
	s += std::format(" {:>3},{:>3}\n", Control.FB, Control.ALG);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += (i < 3)? "\n": ",\"\"}\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMucom(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		if (!IsTimbre){
			if (Line.starts_with("  @")){
				IsTimbre = true;
				
				auto Token = Line.substr(3);
				Replace(Token, "\t", " ");
				Control.NUM = ToValue(Token);
			}
		} else {
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			Replace(Line, ", ", ",");
			Replace(Line, " ,", ",");
			Line = Trim(Line, " ");
			Line = CommentCut(Line, "\"");
			if (Line.ends_with(",")) Line = Line.substr(0, Line.size()-1);
			Replace(Line, ",", " ");
			if (Line.size() == 0) continue;
			
			auto Tokens = GetToken(Line, ' ');
			switch (TimbreLine){
				case 0:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.FB = ToValue(Token);	break;	}
							case 1:{	Control.ALG = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					IsControl = true;
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					GetOperatorOPN(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToPmdOPN(CString& Text)
{
	std::string s;
	s += std::format("@{:03} {:03} {:03}\n", Control.NUM, Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:03}", aOperator[i].AR);
		s += std::format(" {:03}", aOperator[i].DR);
		s += std::format(" {:03}", aOperator[i].SR);
		s += std::format(" {:03}", aOperator[i].RR);
		s += std::format(" {:03}", aOperator[i].SL);
		s += std::format(" {:03}", aOperator[i].TL);
		s += std::format(" {:03}", aOperator[i].KS);
		s += std::format(" {:03}", aOperator[i].MT);
		s += std::format(" {:03}", aOperator[i].DT);
		s += " 000";//AM
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromPmdOPN(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("@")){
				IsTimbre = true;
				IsControl = true;
				
				Replace(Line, "@ ", "@");
				
				auto Tokens = GetToken(Line.substr(1), ' ');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 0:{	Control.NUM = ToValue(Token);	break;	}
						case 1:{	Control.ALG = ToValue(Token);	break;	}
						case 2:{	Control.FB = ToValue(Token);	break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			auto Tokens = GetToken(Line, ' ');
			if (Tokens.size() == 10){
				switch (TimbreLine){
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToPmdOPM(CString& Text)
{
	std::string s;
	s += std::format("@{:03} {:03} {:03}\n", Control.NUM, Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:03}", aOperator[i].AR);
		s += std::format(" {:03}", aOperator[i].D1R);
		s += std::format(" {:03}", aOperator[i].D2R);
		s += std::format(" {:03}", aOperator[i].RR);
		s += std::format(" {:03}", aOperator[i].D1L);
		s += std::format(" {:03}", aOperator[i].TL);
		s += std::format(" {:03}", aOperator[i].KS);
		s += std::format(" {:03}", aOperator[i].MT);
		s += std::format(" {:03}", aOperator[i].DT1);
		s += std::format(" {:03}", aOperator[i].DT2);
		s += std::format(" {:03}", aOperator[i].AME);
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromPmdOPM(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("@")){
				IsTimbre = true;
				IsControl = true;
				
				Replace(Line, "@ ", "@");
				
				auto Tokens = GetToken(Line.substr(1), ' ');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 0:{	Control.NUM = ToValue(Token);	break;	}
						case 1:{	Control.ALG = ToValue(Token);	break;	}
						case 2:{	Control.FB = ToValue(Token);	break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			auto Tokens = GetToken(Line, ' ');
			if (Tokens.size() == 11){
				switch (TimbreLine){
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPM(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmp(CString& Text)
{
	std::string s;
	s += std::format("'@ {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmp(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ ")){
				IsTimbre = true;
				
				auto Token = Line.substr(3);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ',');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmpA(CString& Text)
{
	std::string s;
	s += std::format("'@ A {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmpA(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ A ")){
				IsTimbre = true;
				
				auto Token = Line.substr(5);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ',');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmp7F(CString& Text)
{
	std::string s;
	s += std::format("'@ F {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmp7F(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ F ")){
				IsTimbre = true;
				
				auto Token = Line.substr(5);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ',');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmp7FA(CString& Text)
{
	std::string s;
	s += std::format("'@ FA {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmp7FA(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ FA ")){
				IsTimbre = true;
				
				auto Token = Line.substr(6);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ',');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmp7FC(CString& Text)
{
	std::string s;
	s += std::format("'@ FC {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}", aOperator[i].AME);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmp7FC(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ FC ")){
				IsTimbre = true;
				
				auto Token = Line.substr(6);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ',');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPM(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmF(CString& Text)
{
	std::string s;
	s += std::format("'@ F {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromMml2VgmF(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ F ") && Line.find_first_of("\"") != std::string::npos){
				IsTimbre = true;
				
				auto Token = Line.substr(5);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ' ');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmN(CString& Text)
{
	std::string s;
	s += std::format("'@ N {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += ",  0";//AM
		s += std::format(",{:>3}", aOperator[i].SSG);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromMml2VgmN(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ N ") && Line.find_first_of("\"") != std::string::npos){
				IsTimbre = true;
				
				auto Token = Line.substr(5);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ' ');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
								case 1:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
								case 2:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
								case 3:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
								case 4:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
								case 5:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
								case 6:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
								case 7:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
								case 8:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
								case 9:{	break;	}//AM
								case 10:{	aOperator[iOperator].SSG = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmM(CString& Text)
{
	std::string s;
	s += std::format("'@ M {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}", aOperator[i].AME);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromMml2VgmM(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("'@ M ") && Line.find_first_of("\"") != std::string::npos){
				IsTimbre = true;
				
				auto Token = Line.substr(5);
				Control.NUM = ToValue(Token);
			}
		} else {
			if (Line.starts_with("'@ ")){
				auto Tokens = GetToken(Line.substr(3), ' ');
				switch (TimbreLine){
					case 4:{
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
						IsControl = true;
						break;
					}
					case 0:
					case 1:
					case 2:
					case 3:
					{
						GetOperatorOPM(Tokens, iOperator);
						++iOperator;
						break;
					}
				}
				++TimbreLine;
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMucomDotNET(CString& Text)
{
	std::string s;
	s += std::format("  @M{}\n", Control.NUM);
	s += std::format(" {:>3},{:>3}\n", Control.FB, Control.ALG);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMucomDotNET(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		if (!IsTimbre){
			if (Line.starts_with("  @M")){
				IsTimbre = true;
				
				auto Token = Line.substr(4);
				Replace(Token, "\t", " ");
				Control.NUM = ToValue(Token);
			}
		} else {
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			Replace(Line, ", ", ",");
			Replace(Line, " ,", ",");
			Line = Trim(Line, " ");
			Replace(Line, ",", " ");
			if (Line.size() == 0) continue;
			
			auto Tokens = GetToken(Line, ' ');
			switch (TimbreLine){
				case 0:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.FB = ToValue(Token);	break;	}
							case 1:{	Control.ALG = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					IsControl = true;
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMAmidiMemoMOPN(CString& Text)
{
	std::string s;
	s += "*.mopn\n";
	s += "1.0\n";
	s += "1\n";
	s += std::format("@{}\n", Control.NUM);
	s += std::format("{},{},0,0,0,,\n", Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "1";
		s += std::format(",{}", aOperator[i].AR);
		s += std::format(",{}", aOperator[i].DR);
		s += std::format(",{}", aOperator[i].SR);
		s += std::format(",{}", aOperator[i].RR);
		s += std::format(",{}", aOperator[i].SL);
		s += std::format(",{}", aOperator[i].TL);
		s += std::format(",{}", aOperator[i].KS);
		s += std::format(",{}", aOperator[i].MT);
		s += std::format(",{}", aOperator[i].DT);
		s += ",0";//AM
		s += std::format(",{}", aOperator[i].SSG);
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMAmidiMemoMOPN(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	int Header = 0;
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		if (!IsTimbre){
			switch (Header){
				case 0:{	if (Line.compare("*.mopn") == 0){	++Header; }	break;	}
				case 1:{	if (Line.compare("1.0") == 0){		++Header; }	break;	}
				case 2:{	if (Line.compare("1") == 0){		++Header; }	break;	}
				case 3:{
					if (Line.size() > 0 && Line[0] == '@'){
						auto Token = Trim(Line, "@");
						Control.NUM = ToValue(Token);
					}
					++Header;
					break;
				}
				case 4:{
					IsTimbre = true;
					IsControl = true;
					
					auto Tokens = GetToken(Line, ',');
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.ALG = ToValue(Token);	break;	}
							case 1:{	Control.FB = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					break;
				}
			}
		} else {
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:
				case 1:
				case 2:
				case 3:
				{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	aOperator[iOperator].EN = ToValue(Token);	break;	}
							case 1:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
							case 2:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
							case 3:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
							case 4:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
							case 5:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
							case 6:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
							case 7:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
							case 8:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
							case 9:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
							case 10:{	break;	}//AM
							case 11:{	aOperator[iOperator].SSG = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMAmidiMemoMOPM(CString& Text)
{
	std::string s;
	s += "*.mopm\n";
	s += "1.0\n";
	s += "1\n";
	s += std::format("@{}\n", Control.NUM);
	s += std::format("{},{},0,0,0,,,,,,\n", Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format( "{}", aOperator[i].EN);
		s += std::format(",{}", aOperator[i].AR);
		s += std::format(",{}", aOperator[i].D1R);
		s += std::format(",{}", aOperator[i].D2R);
		s += std::format(",{}", aOperator[i].RR);
		s += std::format(",{}", aOperator[i].D1L);
		s += std::format(",{}", aOperator[i].TL);
		s += std::format(",{}", aOperator[i].KS);
		s += std::format(",{}", aOperator[i].MT);
		s += std::format(",{}", aOperator[i].DT1);
		s += std::format(",{}", aOperator[i].AME);
		s += std::format(",{}", aOperator[i].DT2);
		s += ",0";//LS
		s += ",-1";//KSV
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMAmidiMemoMOPM(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	int Header = 0;
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		if (!IsTimbre){
			switch (Header){
				case 0:{	if (Line.compare("*.mopm") == 0){	++Header; }	break;	}
				case 1:{	if (Line.compare("1.0") == 0){		++Header; }	break;	}
				case 2:{	if (Line.compare("1") == 0){		++Header; }	break;	}
				case 3:{
					if (Line.size() > 0 && Line[0] == '@'){
						auto Token = Trim(Line, "@");
						Control.NUM = ToValue(Token);
					}
					++Header;
					break;
				}
				case 4:{
					IsTimbre = true;
					IsControl = true;
					
					auto Tokens = GetToken(Line, ',');
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.ALG = ToValue(Token);	break;	}
							case 1:{	Control.FB = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					break;
				}
			}
		} else {
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:
				case 1:
				case 2:
				case 3:
				{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	aOperator[iOperator].EN = ToValue(Token);	break;	}
							case 1:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
							case 2:{	aOperator[iOperator].D1R = ToValue(Token);	break;	}
							case 3:{	aOperator[iOperator].D2R = ToValue(Token);	break;	}
							case 4:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
							case 5:{	aOperator[iOperator].D1L = ToValue(Token);	break;	}
							case 6:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
							case 7:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
							case 8:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
							case 9:{	aOperator[iOperator].DT1 = ToValue(Token);	break;	}
							case 10:{	aOperator[iOperator].AME = ToValue(Token);	break;	}
							case 11:{	aOperator[iOperator].DT2 = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToZMusicV(CString& Text)
{
	std::string s;
	s += std::format("(v{},0\n", Control.NUM);
	
	s += "   ";
	s += std::format(" {:>3}", ((Control.FB<<3) | Control.ALG));
	s += std::format(",{:>3}", ((aOperator[3].EN<<3)|(aOperator[2].EN<<2)|(aOperator[1].EN<<1)|aOperator[0].EN));
	s += std::format(",{:>3}", Control.WF);
	s += std::format(",{:>3}", Control.LFR);
	s += std::format(",{:>3}", Control.FRQ);
	s += std::format(",{:>3}", Control.PMD);
	s += std::format(",{:>3}", Control.AMD);
	s += std::format(",{:>3}", Control.PMS);
	s += std::format(",{:>3}", Control.AMS);
	s += ",  3";//PAN
	s += ",  0\n";//Dummy
	
	for (int i = 0; i < _countof(aOperator); ++i){
		s += "   ";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}",  aOperator[i].AME);
		s += (i < 3)? "\n": ")\n";
	}
	
	Text = s.c_str();
}



void CIntermediate::FromZMusicV(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, "/");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("(v")){
				auto Tokens = GetToken(Line.substr(2), ',');
				if (Tokens.size() > 0){
					Control.NUM = ToValue(Tokens[0]);
					
					IsTimbre = true;
				}
			}
		} else {
			Line = CommentCut(Line, ")");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{
								auto AF = ToValue(Token);
								Control.ALG = (AF>>0) & 7;
								Control.FB =  (AF>>3) & 7;
								break;
							}
							case 1:{
								auto EN = ToValue(Token);
								aOperator[0].EN = (EN>>0) & 1;
								aOperator[1].EN = (EN>>1) & 1;
								aOperator[2].EN = (EN>>2) & 1;
								aOperator[3].EN = (EN>>3) & 1;
								break;
							}
							case 2:{	Control.WF = ToValue(Token);	break;	}
							case 3:{	Control.LFR = ToValue(Token);	break;	}
							case 4:{	Control.FRQ = ToValue(Token);	break;	}
							case 5:{	Control.PMD = ToValue(Token);	break;	}
							case 6:{	Control.AMD = ToValue(Token);	break;	}
							case 7:{	Control.PMS = ToValue(Token);	break;	}
							case 8:{	Control.AMS = ToValue(Token);	break;	}
							case 9:{	break;	}//PAN
						}
						++TimbreToken;
					}
					IsControl = true;
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToZMusicAt(CString& Text)
{
	std::string s;
	s += std::format("(@{:<3},", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format("{:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}", aOperator[i].AME);
		s += "\n      ";
	}
	
	s += std::format("{:>3}", Control.ALG);
	s += std::format(",{:>3}", Control.FB);
	s += std::format(",{:>3}", ((aOperator[3].EN<<3)|(aOperator[2].EN<<2)|(aOperator[1].EN<<1)|aOperator[0].EN));
	s += ",  3";//PAN
	s += std::format(",{:>3}", Control.WF);
	s += std::format(",{:>3}", Control.LFR);
	s += std::format(",{:>3}", Control.FRQ);
	s += std::format(",{:>3}", Control.PMD);
	s += std::format(",{:>3}", Control.AMD);
	s += std::format(",{:>3}", Control.PMS);
	s += std::format(",{:>3}", Control.AMS);
	s += ")\n";
	
	Text = s.c_str();
}



void CIntermediate::FromZMusicAt(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, "/");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("(@")){
				auto Tokens = GetToken(Line.substr(2), ',');
				if (Tokens.size() > 0){
					Control.NUM = ToValue(Tokens[0]);
					Tokens.erase(Tokens.begin());
					
					if (Tokens.size() > 0){
						GetOperatorOPM(Tokens, iOperator);
						++iOperator;
					}
					
					IsTimbre = true;
					IsControl = true;
				}
			}
		} else {
			Line = CommentCut(Line, ")");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 3:
				case 4:
				{
					if (iOperator < _countof(aOperator)){
						GetOperatorOPM(Tokens, iOperator);
						++iOperator;
					} else {
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{	Control.ALG = ToValue(Token);	break;	}
								case 1:{	Control.FB = ToValue(Token);	break;	}
								case 2:{
									auto EN = ToValue(Token);
									aOperator[0].EN = (EN>>0) & 1;
									aOperator[1].EN = (EN>>1) & 1;
									aOperator[2].EN = (EN>>2) & 1;
									aOperator[3].EN = (EN>>3) & 1;
									break;
								}
								case 3:{	break;	}//PAN
								case 4:{	Control.WF = ToValue(Token);	break;	}
								case 5:{	Control.LFR = ToValue(Token);	break;	}
								case 6:{	Control.FRQ = ToValue(Token);	break;	}
								case 7:{	Control.PMD = ToValue(Token);	break;	}
								case 8:{	Control.AMD = ToValue(Token);	break;	}
								case 9:{	Control.PMS = ToValue(Token);	break;	}
								case 10:{	Control.AMS = ToValue(Token);	break;	}
							}
							++TimbreToken;
						}
					}
					break;
				}
				case 0:
				case 1:
				case 2:
				{
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToNagDrv(CString& Text)
{
	std::string s;
	s += std::format("VS {:<3}", Control.NUM);
	s += "={";
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format("{:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}", aOperator[i].AME);
		s += "\n        ";
	}
	
	s += std::format("{:>3}", Control.ALG);
	s += std::format(",{:>3}", Control.FB);
	s += std::format(",{:>3}", ((aOperator[3].EN<<3)|(aOperator[2].EN<<2)|(aOperator[1].EN<<1)|aOperator[0].EN));
	s += ",  3";//PAN
	s += ",  0";//VOL
	s += "}\n";
	
	Text = s.c_str();
}



void CIntermediate::FromNagDrv(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, "*");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("VS ")){
				Line = Line.substr(3);
				Replace(Line, "=", ",");
				Replace(Line, "{", " ");
				
				auto Tokens = GetToken(Line, ',');
				if (Tokens.size() > 0){
					Control.NUM = ToValue(Tokens[0]);
					Tokens.erase(Tokens.begin());
					
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					
					IsTimbre = true;
					IsControl = true;
				}
			}
		} else {
			Line = CommentCut(Line, "}");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 3:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.ALG = ToValue(Token);	break;	}
							case 1:{	Control.FB = ToValue(Token);	break;	}
							case 2:{
								auto EN = ToValue(Token);
								aOperator[0].EN = (EN>>0) & 1;
								aOperator[1].EN = (EN>>1) & 1;
								aOperator[2].EN = (EN>>2) & 1;
								aOperator[3].EN = (EN>>3) & 1;
								break;
							}
							case 3:{	break;	}//PAN
							case 4:{	break;	}//VOL
						}
						++TimbreToken;
					}
					break;
				}
				case 0:
				case 1:
				case 2:
				{
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToNrtDrv(CString& Text)
{
	std::string s;
	s += std::format("@{}", Control.NUM);
	s += " {\n";
	
	s += std::format(" {:>3}", ((Control.FB<<3) | Control.ALG));
	s += std::format(",{:>3}", ((aOperator[3].EN<<3)|(aOperator[2].EN<<2)|(aOperator[1].EN<<1)|aOperator[0].EN));
	s += std::format(" {:>3}", Control.WF);
	s += std::format(" {:>3}", Control.LFR);
	s += std::format(" {:>3}", Control.FRQ);
	s += std::format(" {:>3}", Control.PMD);
	s += std::format(" {:>3}", Control.AMD);
	s += std::format(" {:>3}", Control.PMS);
	s += std::format(" {:>3}", Control.AMS);
	s += ",  3";//PAN
	s += ",  0";//NOI
	s += "\n";
	
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].D1R);
		s += std::format(",{:>3}", aOperator[i].D2R);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].D1L);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT1);
		s += std::format(",{:>3}", aOperator[i].DT2);
		s += std::format(",{:>3}", aOperator[i].AME);
		s += "\n";
	}
	s += "}\n";
	
	Text = s.c_str();
}



void CIntermediate::FromNrtDrv(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, ";");
		
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		Replace(Line, ", ", ",");
		Replace(Line, " ,", ",");
		Line = Trim(Line, " ");
		//Replace(Line, ",", " ");
		if (Line.size() == 0) continue;
		
		if (!IsTimbre){
			if (Line.starts_with("@") && Line.find_first_of("{") != std::string::npos){
				Line = Line.substr(1);
				Line = CommentCut(Line, "{");
				
				auto Tokens = GetToken(Line, ',');
				if (Tokens.size() > 0){
					Control.NUM = ToValue(Tokens[0]);
					
					IsTimbre = true;
					IsControl = true;
				}
			}
		} else {
			Line = CommentCut(Line, "}");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{
								auto AF = ToValue(Token);
								Control.ALG = (AF>>0) & 7;
								Control.FB =  (AF>>3) & 7;
								break;
							}
							case 1:{
								auto EN = ToValue(Token);
								aOperator[0].EN = (EN>>0) & 1;
								aOperator[1].EN = (EN>>1) & 1;
								aOperator[2].EN = (EN>>2) & 1;
								aOperator[3].EN = (EN>>3) & 1;
								break;
							}
							case 2:{	Control.WF = ToValue(Token);	break;	}
							case 3:{	Control.LFR = ToValue(Token);	break;	}
							case 4:{	Control.FRQ = ToValue(Token);	break;	}
							case 5:{	Control.PMD = ToValue(Token);	break;	}
							case 6:{	Control.AMD = ToValue(Token);	break;	}
							case 7:{	Control.PMS = ToValue(Token);	break;	}
							case 8:{	Control.AMS = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					GetOperatorOPM(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToN88Basic(CString& Text)
{
	std::string s;
	int Line = Control.NUM;
	Line = (Line > 0)? Line: 1;
	
	s += std::format("{}0 DATA", Line++);
	s += std::format(" {:>3}", ((Control.FB<<3) | Control.ALG));
	s += std::format(",{:>3}", ((aOperator[3].EN<<3)|(aOperator[2].EN<<2)|(aOperator[1].EN<<1)|aOperator[0].EN));
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += ",  0";
	s += "\n";
	
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format("{}0 DATA", Line++);
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += ",  0";
		s += "\n";
	}
	
	Text = s.c_str();
}



void CIntermediate::FromN88Basic(const CString& Text)
{
	auto IsTimbre = false;
	auto IsControl = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Line = CommentCut(Line, "'");
		
		auto DATA = Line.find("DATA");
		if (DATA != std::string::npos){
			auto Head = Line.substr(0, DATA);
			
			Line = Line.substr(DATA+4);
			
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			Replace(Line, ", ", ",");
			Replace(Line, " ,", ",");
			Line = Trim(Line, " ");
			//Replace(Line, ",", " ");
			if (Line.size() == 0) continue;
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:{
					if (Tokens.size() == 10){
						Control.NUM = ToValue(Head) / 10;
						
						int TimbreToken = 0;
						for (auto Token : Tokens){
							switch (TimbreToken){
								case 0:{
									auto AF = ToValue(Token);
									Control.ALG = (AF>>0) & 7;
									Control.FB =  (AF>>3) & 7;
									break;
								}
								case 1:{
									auto EN = ToValue(Token);
									aOperator[0].EN = (EN>>0) & 1;
									aOperator[1].EN = (EN>>1) & 1;
									aOperator[2].EN = (EN>>2) & 1;
									aOperator[3].EN = (EN>>3) & 1;
									break;
								}
							}
							++TimbreToken;
						}
						IsTimbre = true;
						IsControl = true;
						
						++TimbreLine;
					}
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					if (Tokens.size() == 10){
						GetOperatorOPN(Tokens, iOperator);
						++iOperator;
						
						++TimbreLine;
					}
					break;
				}
			}
		}
	}
	if (!(IsTimbre && IsControl && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}
