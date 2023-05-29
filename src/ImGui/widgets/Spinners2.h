#pragma once

#include "imspinner.h"

// Tiny additions by @moebiusSurfing
namespace ImSpinner
{
	// By moebiusSurfing
	//TODO: draw some selected widgets from the demo
	inline void Spinner(bool bOn, int n)
	{
		float velocity = 1.f;
		//static float velocity = 1.f;

		static float nextdot = 0, nextdot2;
		nextdot -= 0.07f;

		// Make empty space when hidden
		if (!bOn)
		{
			// y spacing
			float oy = 0;
			oy += 44;
			//oy -= ImGui::GetStyle().ItemSpacing.y;
			auto pt = ImGui::GetCursorPos() + ImVec2(0, oy);
			ImGui::SetCursorPos(pt);

			return;
		}

		static int cci = 0, last_cci = 0;
		static std::map<int, float> __rr; auto R = [](float v) { if (!__rr.count(cci)) { __rr[cci] = v; }; return __rr[cci]; };
		static std::map<int, float> __tt; auto T = [](float v) { if (!__tt.count(cci)) { __tt[cci] = v; }; return __tt[cci];  };
		static std::map<int, ImColor> __cc; auto C = [](ImColor v) { if (!__cc.count(cci)) { __cc[cci] = v; }; return __cc[cci];  };
		static std::map<int, ImColor> __cb; auto CB = [](ImColor v) { if (!__cb.count(cci)) { __cb[cci] = v; }; return __cb[cci];  };
		static std::map<int, bool> __hc; auto HC = [](bool v) { if (!__hc.count(cci)) { __hc[cci] = v; }; return __hc[cci];  };
		static std::map<int, bool> __hcb; auto HCB = [](bool v) { if (!__hcb.count(cci)) { __hcb[cci] = v; }; return __hcb[cci];  };
		static std::map<int, float> __ss; auto S = [](float v) { if (!__ss.count(cci)) { __ss[cci] = v; }; return __ss[cci];  };
		static std::map<int, float> __aa; auto A = [](float v) { if (!__aa.count(cci)) { __aa[cci] = v; }; return __aa[cci];  };
		static std::map<int, float> __amn; auto AMN = [](float v) { if (!__amn.count(cci)) { __amn[cci] = v; }; return __amn[cci];  };
		static std::map<int, float> __amx; auto AMX = [](float v) { if (!__amx.count(cci)) { __amx[cci] = v; }; return __amx[cci];  };
		static std::map<int, int> __dt; auto DT = [](int v) { if (!__dt.count(cci)) { __dt[cci] = v; }; return __dt[cci];  };
		static std::map<int, int> __mdt; auto MDT = [](int v) { if (!__mdt.count(cci)) { __mdt[cci] = v; }; return __mdt[cci];  };
		static std::map<int, float> __dd; auto D = [](float v) { if (!__dd.count(cci)) { __dd[cci] = v; }; return __dd[cci];  };

		switch (n)
		{
		case /*4*/ 0: ImSpinner::Spinner<e_st_ang>("SpinnerAng270",
			Radius{ R(16) }, Thickness{ T(2) }, Color{ C(white) }, BgColor{ CB(ImColor(255, 255, 255, 128)) }, Speed{ S(6) * velocity }, Angle{ A(0.75f * PI_2) }); break;

		case /*51*/ 1: ImSpinner::SpinnerFluid("SpinnerFluid",
			R(16), C(ImColor(0, 0, 255)), S(3.8f) * velocity, 4); break;

		case /*57*/ 2: ImSpinner::SpinnerPulsar("SpinnerPulsar",
			R(16), T(2), C(white), S(1) * velocity, false); break;

		case /*60*/ 3: ImSpinner::SpinnerFilledArcFade("SpinnerFilledArcFade6",
			R(16), C(white), S(6) * velocity, 6); break;

		case /*70*/ 4: ImSpinner::SpinnerLemniscate("SpinnerLemniscate",
			R(20), T(3), C(white), S(2.1f) * velocity, 3); break;

		case /*72*/ 5: ImSpinner::SpinnerRotatedAtom("SpinnerRotatedAtom",
			R(16), T(2), C(white), S(2.1f) * velocity, 3); break;

		case /*81*/ 6: ImSpinner::SpinnerRotateTriangles("SpinnerRotateTriangles",
			R(16), T(2), C(white), S(6.f) * velocity, 3); break;

		case /*103*/ 7: ImSpinner::SpinnerPatternRings("SpinnerPatternRings",
			R(16), T(2), C(white), S(4.1f) * velocity, DT(3)); break;

		case /*109*/ 8: ImSpinner::SpinnerCircularPoints("SpinnerCircularPoints",
			R(16), T(1.2f), C(white), S(10.f) * velocity, DT(7));  break;

		case /*131*/ 9: ImSpinner::SpinnerSolarScaleBalls("SpinnerSolarScaleBalls",
			R(16), T(1.3f), C(red), S(1) * velocity, DT(36)); break;

		case /*$(46) */10: ImSpinner::SpinnerGooeyBalls("SpinnerGooeyBalls",
			R(16), C(white), S(2.f) * velocity); break;

		case /*$(47)*/ 11: ImSpinner::SpinnerRotateGooeyBalls("SpinnerRotateGooeyBalls2",
			R(16), T(5), C(white), S(6.f) * velocity, 2); break;

		case /*$(3)*/ 12: ImSpinner::Spinner<e_st_ang>("SpinnerAngNoBg",
			Radius{ R(16) }, Thickness{ T(2) }, Color{ C(white) }, BgColor{ CB(ImColor(255, 255, 255, 0)) }, Speed{ S(6) * velocity }, Angle{ A(IM_PI) }); break;

		case /*$(2)*/ 13: ImSpinner::Spinner<e_st_dots>("SpinnerDots",
			Radius{ R(16) }, Thickness{ T(4) }, Color{ C(white) }, FloatPtr{ &nextdot }, Speed{ S(1) * velocity }, Dots{ DT(12) }, MinThickness{ -1.f }); break;

		case /*$(24)*/ 14: ImSpinner::SpinnerIncScaleDots("SpinnerIncScaleDots",
			R(16), T(4), C(white), S(6.6f) * velocity, 6); break;

		}
	}

	static int amountSpinners = 15;
	// = ImSpinner::amountSpinners;
}
