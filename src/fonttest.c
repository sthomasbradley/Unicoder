#include "unicoder.h"

int main()
{
    int i;
    int oldmode;

    oldmode = ucharOn();

    wprintf(L"4.1. Greek     4.2. Modified      4.4. Numbers   4.5. Fractions\n");
    wprintf(L"                    Greek      \n");

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_alpha,U_supalpha,U_Alpha,U_vtsolid,U_zeta,U_Zeta,U_vtsolid);

    wprintf(L"  %lc  %lc %lc%lc %lc",U_vtsolid,U_baralpha,U_alphatilde,U_vtsolid,U_vtsolid);
    wprintf(L"          %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup0,U_sub0,U_ltcircle0,U_dkcircle0,U_vtsolid,U_ltcircle10,U_dkcircle10,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc \n",U_vtsolid,U_oneeighth,U_onesixth,U_onefifth,U_onefourth,U_onethird,U_onehalf, U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_beta,U_supbeta,U_subbeta,U_Beta,U_vtsolid,U_eta,U_Eta,U_vtsolid);
    wprintf(L"  %lc%lc    %lc%lc%lc",U_vtsolid,U_theta2nd,U_vtsolid,U_Theta2nd,U_vtsolid);
    wprintf(L"          %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup1,U_sub1,U_ltcircle1,U_dkcircle1,
              U_vtsolid,U_ltcircle11,U_dkcircle11,U_vtsolid);
    wprintf(L"  %lc%lc   %lc   %lc  %lc \n",U_vtsolid,U_threeeighths,U_twofifths,U_twothirds, U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_gamma,U_supgamma,U_subgamma,U_Gamma,U_vtsolid,U_kappa,U_Kappa,U_vtsolid);
    wprintf(L"  %lc%lc   %lc%lc%lc%lc",U_vtsolid,U_iota2nd,U_iotatilde,U_vtsolid,U_Iota2nd,U_vtsolid);
    wprintf(L"          %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup2,U_sub2,U_ltcircle2,U_dkcircle2,U_vtsolid,U_ltcircle12,U_dkcircle12,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc    %lc \n",U_vtsolid,U_fiveeighths,U_fivesixths,U_threefifths,U_threequarter,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_delta,U_supdelta,U_Delta,U_vtsolid,U_lambda,U_Lambda,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc%lc%lc%lc",U_vtsolid,U_upsilon2nd,U_barupsilon,U_upsilontilde,U_vtsolid,U_Upsilon2nd,U_vtsolid);
    wprintf(L"          %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup3,U_sub3,U_ltcircle3,U_dkcircle3,U_vtsolid,U_ltcircle13,U_dkcircle13,U_vtsolid);
    wprintf(L"  %lc%lc   %lc      %lc \n",U_vtsolid,U_seveneighths,U_fourfifths, U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_epsilon,U_supepsilon,U_Epsilon,U_vtsolid,U_mu,U_Mu,U_vtsolid);
    wprintf(L"  %lc  %lc %lc%lc %lc",U_vtsolid,U_baromega,U_omegatilde,U_vtsolid,U_vtsolid);
    wprintf(L"          %lc%lc %lc %lc %lc%lc%lc %lc%lc\n",U_vtsolid,U_sup4,U_sub4,U_ltcircle4,U_dkcircle4,U_vtsolid,U_ltcircle14,U_dkcircle14,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc             ",U_vtsolid,U_theta,U_suptheta,U_Theta,U_vtsolid,U_nu,U_Nu,U_vtsolid,U_vtsolid);
    wprintf(L"        %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup5,U_sub5,U_ltcircle5,U_dkcircle5,U_vtsolid,U_ltcircle15,U_dkcircle15,U_vtsolid);
    wprintf(L"  4.7. Geometric\n");

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_iota,U_supiota,U_Iota,U_vtsolid,U_xi,U_Xi,U_vtsolid);
    wprintf(L"  4.3. Mathematical");
    wprintf(L"  %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup6,U_sub6,U_ltcircle6,U_dkcircle6,U_vtsolid,U_ltcircle16,U_dkcircle16,U_vtsolid);
    wprintf(L"       shapes\n");

    wprintf(L"%lc%lc   %lc %lc%lc%lc %lc%lc",U_vtsolid,U_rho,U_subrho,U_Rho,U_vtsolid,U_omicron,U_Omicron,U_vtsolid);
    wprintf(L"       symbols");
    wprintf(L"       %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup7,U_sub7,U_ltcircle7,U_dkcircle7,U_vtsolid,U_ltcircle17,U_dkcircle17,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_blacksqr,U_blacksqrsm,U_box,U_boxsm,U_spades,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_upsilon,U_supupsilon,U_Upsilon,U_vtsolid,U_pi,U_Pi,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc0%lc.0%lc",U_vtsolid,U_minussign,U_supminus,U_subminus,U_vtsolid,U_partial,U_infty,
            U_vtsolid,U_comboseconds,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup8,U_sub8,U_ltcircle8,U_dkcircle8,U_vtsolid,U_ltcircle18,U_dkcircle18,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_blackcircle,U_inversecircle,U_circle,U_litecircle,U_clubs,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_phi,U_supphi,U_Phi,U_vtsolid,U_sigma,U_Sigma,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_pm,U_supplus,U_subplus,U_vtsolid,U_sum,U_emptyset,
            U_vtsolid,U_combo1stderiv,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_sup9,U_sub9,U_ltcircle9,U_dkcircle9,U_vtsolid,U_ltcircle19,U_dkcircle19,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_blacksqrlow,U_blacksqrhigh,U_swirl,U_lozenge,U_diamonds,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_chi,U_supchi,U_subchi,U_Chi,U_vtsolid,U_tau,U_Tau,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_equiv,U_supequal,U_subequal,U_vtsolid,U_prod,U_exists,
            U_vtsolid,U_combo2ndderiv,U_vtsolid);
    wprintf(L"  %lc       %lc%lc %lc%lc",U_vtsolid,U_vtsolid,U_ltcircle20,U_dkcircle20,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_blackblock,U_darkblock,U_mediumblock,U_liteblock,U_hearts,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc%lc%lc %lc%lc",U_vtsolid,U_psi,U_suppsi,U_subpsi,U_Psi,U_vtsolid,U_omega,U_Omega,U_vtsolid);
    wprintf(L"  %lc %lc %lc  %lc%lc %lc%lc %lca %lc",U_vtsolid,U_neq,U_supintgl,U_vtsolid,U_intgl,U_dagger,
            U_vtsolid,U_combohat,U_vtsolid);
    wprintf(L"                 %lc%lc %lc      %lc\n",U_vtsolid,U_blktriangle,U_blktrianglesm,U_vtsolid);

    wprintf(L"%lc%lc      %lc%lc %lc%lc",U_vtsolid,U_varbeta,U_vtsolid,U_kai,U_kai,U_vtsolid);
    wprintf(L"  %lc %lc    %lc%lc %lc%lc %lca %lc",U_vtsolid,U_approx,U_vtsolid,U_sqrt,U_dbldagr,
            U_vtsolid,U_combotilde,U_vtsolid);
    wprintf(L"  4.6. Symbols");
    wprintf(L"   %lc%lc %lc     %lc%lc\n",U_vtsolid,U_blkdwnarw,U_blkdwnarwsm,U_8thnote,U_vtsolid);

    wprintf(L"%lc%lc      %lc%lc %lc%lc",U_vtsolid,U_vargamma,U_vtsolid,U_koppa,U_Koppa,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_less,U_leq,U_ll,U_vtsolid,U_increment,U_cap,
            U_vtsolid,U_combobar,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc",U_vtsolid,U_Angstrom,U_careof,U_Warrow,U_subleftarw,U_lefthead,U_lthappy,U_vtsolid);
    wprintf(L"  %lc%lc %lc     %lc%lc\n",U_vtsolid,U_blklftarw,U_blklftarwsm,U_beamed8th,U_vtsolid);

    wprintf(L"%lc%lc      %lc%lc %lc%lc",U_vtsolid,U_varepsilon,U_vtsolid,U_digamma,U_Digamma,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_greater,U_geq,U_gg,U_vtsolid,U_lnell,U_forall,
            U_vtsolid,U_comboxabove,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc",U_vtsolid,U_Degree,U_copyright,U_Earrow,U_combsubrgtarw,U_rgthead,U_dkhappy,U_vtsolid);
    wprintf(L"  %lc%lc %lc     %lc%lc\n",U_vtsolid,U_blkrgtarw,U_blkrgtarwsm,U_sharp,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc %lc%lc",U_vtsolid,U_vartheta,U_varsuptheta,U_VarOmega,U_vtsolid,U_sampi,U_Sampi,U_vtsolid);
        wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_times,U_crossprod,U_dotprod,U_vtsolid,U_esh,U_circldot,
            U_vtsolid,U_comboxbelow,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_Micro,U_numero,U_Narrow,U_supNarrow,U_subuphead,U_dkstar,U_vtsolid);

    wprintf(L"%lc%lc     %lc%lc%lc %lc%lc",U_vtsolid,U_varsigma,U_VarSigma,U_vtsolid,U_heta,U_Heta,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_div,U_divslash,U_cdot,U_vtsolid,U_neg,U_revneg,
            U_vtsolid,U_combounderline,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc",U_vtsolid,U_Mhos,U_permile,U_Sarrow,U_supSarrow,U_subdownhead,U_female,U_vtsolid);
    wprintf(L"  4.8 Characters\n");

    wprintf(L"%lc%lc     %lc%lc   %lc",U_vtsolid,U_varupsilon,U_VarUpsilon,U_vtsolid,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_squared,U_cubed,U_ordinal,U_vtsolid,U_belongsto,U_contains,
            U_vtsolid,U_combolowinfty,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc",U_vtsolid,U_Ohms,U_registered,U_WEarrow,U_combosublrarw,U_sublefthead,U_male,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_section,U_lowdot,U_leftquot,U_leftsnglquot,U_supopen,U_subopen,U_vtsolid);

    wprintf(L"%lc%lc %lc   %lc%lc%lc  %lc",U_vtsolid,U_varphi,U_varsupphi,U_varGamma,U_vtsolid,U_finalsigma,U_vtsolid);
    wprintf(L"  %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_prime,U_diprime,U_triprime,U_vtsolid,U_intgltop,U_intglbtm,
            U_vtsolid,U_combolowplus,U_vtsolid);

    wprintf(L"  %lc%lc %lc %lc   %lc %lc%lc",U_vtsolid,U_Wavelen,U_soundrecd,U_NSarrow,U_subrgthead,U_sunshine,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_paragraph,U_highdot,U_rgtquot,U_rgtsnglquot,U_supclose,U_subclose,U_vtsolid);

    wprintf(L"%lc%lc     %lc%lc   %lc",U_vtsolid,U_varkoppa,U_VarKoppa,U_vtsolid,U_vtsolid);
    wprintf(L"  %lc %lc %lc  %lc%lc %lc%lc %lca %lc",U_vtsolid,U_transpose,U_rightangle,U_vtsolid,U_lpartop,U_lparbtm,
            U_vtsolid,U_combolowminus,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc   %lc%lc",U_vtsolid,U_RedPlanck,U_trademark,U_uphead,U_downhead,U_house,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_tie,U_2vtdots,U_lowquot,U_lowsnglquot,U_suptilde,U_subtilde,U_vtsolid);

    wprintf(L"               %lc %lc %lc %lc%lc%lc %lc%lc %lca %lc",U_vtsolid,U_imaginary,U_eulersnum,U_estimate,U_vtsolid,U_rpartop,U_rparbtm,
            U_vtsolid,U_combolowaster,U_vtsolid);
    wprintf(L"                 %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_bullet,U_4vtdots,U_reversed,U_revsnglquot,U_supinvtexclm,U_supexclm,U_vtsolid);

    wprintf(L"                                                 ");
    wprintf(L"%lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_litebullet,U_diaeresis,U_caron,U_acute,U_invertexclm,U_dblexclm,U_vtsolid);

    wprintf(L"                                                 %lc  %lc %lc %lc %lc %lc%lc\n",
            U_vtsolid,U_ellipsis,U_cedilla,U_obliquehyphen,U_invertquestn,U_exclmsm,U_vtsolid);
    for(i=0;i<66;i++)
        wprintf(L"%lc",U_hzdbl);
    wprintf(L"\n");

    wprintf(L"4.9. Latin Modifiers   4.10. Latin Modifiers    4.13. Latin Small\n");
    wprintf(L"     Lower case              Upper case               Capitals\n");

    wprintf(L"%lc%lc %lc %lc   %lc   %lc   %lc %lc%lc%lc%lc",U_vtsolid,U_supa,U_suba,U_supf,U_supk,U_supp,U_supv,U_subv,U_vtsolid,U_dli,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_supA,U_supG,U_supK,U_supO,U_supU,U_vtsolid);
    wprintf(L"            %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_smallcapA,U_smallcapE,U_smallcapJ,U_smallcapN,U_smallcapT,U_smallcapX,U_vtsolid);

    wprintf(L"%lc%lc   %lc   %lc   %lc %lc %lc  %lc%lc%lc",U_vtsolid,U_supb,U_supg,U_supl,U_supr,U_subr,U_supw,U_vtsolid,U_dlj,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_supB,U_supH,U_supL,U_supP,U_supV,U_vtsolid);
    wprintf(L"            %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_smallcapB,U_smallcapG,U_smallcapK,U_smallcapO,U_smallcapU,U_smallcapY,U_vtsolid);

    wprintf(L"%lc%lc   %lc   %lc   %lc   %lc %lc%lc %lc",U_vtsolid,U_supc,U_suph,U_supm,U_sups,U_supx,U_subx,U_vtsolid,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_supD,U_supI,U_supM,U_supR,U_supW,U_vtsolid);
    wprintf(L"            %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_smallcapC,U_smallcapH,U_smallcapL,U_smallcapP,U_smallcapV,U_smallcapZ,U_vtsolid);

    wprintf(L"%lc%lc   %lc %lc %lc   %lc   %lc  %lc %lc",U_vtsolid,U_supd,U_supi,U_subi,U_supn,U_supt,U_supy,U_vtsolid,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc  %lc",U_vtsolid,U_supE,U_supJ,U_supN,U_supT,U_vtsolid);
    wprintf(L"            %lc%lc %lc %lc %lc %lc  %lc\n",U_vtsolid,U_smallcapD,U_smallcapI,U_smallcapM,U_smallcapR,U_smallcapW,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc %lc %lc %lc %lc %lc  %lc %lc\n\n",U_vtsolid,U_supe,U_sube,U_supj,U_subj,U_supo,U_subo,U_supu,U_subu,U_supz,U_vtsolid,U_vtsolid);
//
    wprintf(L"4.11. Latin Modified                            4.15. Currency\n");
    wprintf(L"%lc%lc %lc %lc %lc %lc%lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_a1st,U_a2nd,U_ahat,U_abar,U_atilde,
            U_vtsolid,U_A1ST,U_A2ND,U_Ahat,U_Abar,U_Atilde,U_vtsolid);
    wprintf(L"%lc%lc        %lc%lc        %lc",U_vtsolid,U_b1st,U_vtsolid,U_B1ST,U_vtsolid);
    wprintf(L"    %lc%lc %lc %lc %lc %lc%lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_o1st,U_o2nd,U_ohat,U_obar,U_otilde,
            U_vtsolid,U_O1ST,U_O2ND,U_Ohat,U_Obar,U_Otilde,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_austral,U_dong,U_hryvnia,U_mill,U_pound,U_tenge,U_vtsolid);

    wprintf(L"%lc%lc   %lc    %lc%lc   %lc    %lc",U_vtsolid,U_c1st,U_chat,U_vtsolid,U_C1ST,U_Chat,U_vtsolid);
     wprintf(L"    %lc%lc        %lc%lc        %lc",U_vtsolid,U_p1st,U_vtsolid,U_P1ST,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_baht,U_drachma,U_indiarupee,U_naria,U_ruble,U_tugrik,U_vtsolid);

    wprintf(L"%lc%lc        %lc%lc        %lc",U_vtsolid,U_d1st,U_vtsolid,U_D1ST,U_vtsolid);
    wprintf(L"    %lc%lc        %lc%lc        %lc",U_vtsolid,U_r1st,U_vtsolid,U_R1ST,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_bitcoin,U_euro,U_kip,U_peseta,U_rupee,U_turkeylira,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc %lc%lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_e1st,U_e2nd,U_ehat,U_ebar,U_etilde,
            U_vtsolid,U_E1ST,U_E2ND,U_Ehat,U_Ebar,U_Etilde,U_vtsolid);
    wprintf(L"    %lc%lc   %lc    %lc%lc   %lc    %lc",U_vtsolid,U_s1st,U_shat,U_vtsolid,U_S1ST,U_Shat,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_cent,U_franc,U_lira,U_peso,U_shekel,U_won,U_vtsolid);

    wprintf(L"%lc%lc        %lc%lc        %lc",U_vtsolid,U_f1st,U_vtsolid,U_F1ST,U_vtsolid);
    wprintf(L"    %lc%lc %lc      %lc%lc        %lc",U_vtsolid,U_t1st,U_t2nd,U_vtsolid,U_T1ST,U_vtsolid);
    wprintf(L"  %lc%lc %lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_currency,U_guarani,U_livre,U_pfennig,U_spesmilo,U_yen,U_vtsolid);

    wprintf(L"%lc%lc   %lc %lc  %lc%lc   %lc %lc  %lc",U_vtsolid,U_g1st,U_ghat,U_gbar,U_vtsolid,U_G1ST,U_Ghat,U_Gbar,U_vtsolid);
    wprintf(L"    %lc  %lc %lc %lc %lc%lc  %lc %lc %lc %lc%lc\n",U_vtsolid,U_u2nd,U_uhat,U_ubar,U_utilde,
            U_vtsolid,U_U2ND,U_Uhat,U_Ubar,U_Utilde,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc    %lc%lc %lc %lc    %lc",U_vtsolid,U_h1st,U_h2nd,U_hhat,U_vtsolid,U_H1ST,U_H2ND,U_Hhat,U_vtsolid);
    wprintf(L"    %lc        %lc%lc        %lc%lc\n",U_vtsolid,U_vtilde,U_vtsolid,U_Vtilde,U_vtsolid);

    wprintf(L"%lc%lc %lc %lc %lc %lc%lc%lc %lc %lc %lc %lc%lc",U_vtsolid,U_i1st,U_i2nd,U_ihat,U_ibar,U_itilde,
            U_vtsolid,U_I1ST,U_I2ND,U_Ihat,U_Ibar,U_Itilde,U_vtsolid);
    wprintf(L"    %lc%lc %lc %lc    %lc%lc %lc %lc    %lc\n",U_vtsolid,U_w1st,U_w2nd,U_what,U_vtsolid,U_W1ST,U_W2ND,U_What,U_vtsolid);

    wprintf(L"%lc%lc   %lc    %lc    %lc    %lc",U_vtsolid,U_j1st,U_jhat,U_vtsolid,U_Jhat,U_vtsolid);
    wprintf(L"    %lc%lc %lc      %lc%lc %lc      %lc\n",U_vtsolid,U_x1st,U_x2nd,U_vtsolid,U_X1ST,U_X2ND,U_vtsolid);

    wprintf(L"%lc%lc        %lc%lc        %lc",U_vtsolid,U_m1st,U_vtsolid,U_M1ST,U_vtsolid);
    wprintf(L"    %lc%lc %lc %lc %lc %lc%lc%lc %lc %lc %lc %lc%lc\n",U_vtsolid,U_y1st,U_y2nd,U_yhat,U_ybar,U_ytilde,
            U_vtsolid,U_Y1ST,U_Y2ND,U_Yhat,U_Ybar,U_Ytilde,U_vtsolid);

    wprintf(L"%lc%lc       %lc%lc%lc       %lc%lc",U_vtsolid,U_n1st,U_ntilde,U_vtsolid,U_N1ST,U_Ntilde,U_vtsolid);
    wprintf(L"    %lc%lc   %lc    %lc%lc   %lc    %lc\n",U_vtsolid,U_z1st,U_zhat,U_vtsolid,U_Z1ST,U_Zhat,U_vtsolid);

    for(i=0;i<66;i++)
        wprintf(L"%lc",U_hzdbl);
    wprintf(L"\n");
//
    wprintf(L"4.14. Box Drawing  \n");
    wprintf(L"%lc%lc %lc%lc%lc %lc %lc%lc%lc   %lc%lc\n",U_vtsolid,U_vtdash,U_hzdash,U_vtsolid,U_tla,U_tma,U_tra,U_vtsolid,U_tmh,U_tmj,U_vtsolid);
    wprintf(L"%lc%lc %lc%lc%lc %lc %lc%lc%lc   %lc%lc\n",U_vtsolid,U_vtsolid,U_hzb,U_vtsolid,U_mla,U_mma,U_mra,U_vtsolid,U_tmi,U_tmk,U_vtsolid);
    wprintf(L"%lc%lc %lc%lc%lc %lc %lc%lc     %lc\n",U_vtsolid,U_vtsolid,U_vtsolid,U_vtsolid,U_bla,U_bma,U_bra,U_vtsolid,U_vtsolid);
    wprintf(L"%lc%lc %lc%lc     %lc%lc   %lc%lc\n",U_vtsolid,U_vtdashs,U_hzdashs,U_vtsolid,U_vtsolid,U_hzdashs,U_bmj,U_vtsolid);

    return 0;
}

