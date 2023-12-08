#include <gtest/gtest.h>

#include <day8.hpp>

#include <string_view>

namespace {

constexpr std::string_view exercise_input{
    "LRLRRLRLRRRLRRRLRRLRLLRLRLRRRLRLRRLLRRLLRRRLLRRRLRRRLRRLLRLRRRLRRLRLRLLRRLLRRRLLRLRRRLRRRLLRLRRRLLRLLRRLRLRRRLLRLRLLRRRLLRLRRRLLLRRRLLLRRLLLRRRLLRLRLRLRRLLRRRLRRLRRRLRRLRRRLRLRRLRLRRRLRLRRRLRRLRRRLRLLLRLRRRLRLLRLRRLRRRLRRLRLRLRLRRLRRLLRLLLRLRLRRRLRRRLLRLLRLRRLRRRLRRLRRRLRLRRRR\n"
    "\n"
    "JKT = (KFV, CFQ)\n"
    "SQQ = (RLK, TRV)\n"
    "CVT = (KRT, NCV)\n"
    "JVS = (GXT, QMF)\n"
    "KPF = (GCH, FCH)\n"
    "XTQ = (GFM, FSP)\n"
    "QBJ = (PXR, FMK)\n"
    "KXQ = (FMK, PXR)\n"
    "LTM = (CML, TMP)\n"
    "CMD = (DFJ, GXS)\n"
    "VJK = (KGN, HBX)\n"
    "QTP = (KBP, CNM)\n"
    "MBT = (GTN, QXG)\n"
    "HGQ = (PFJ, FXL)\n"
    "MDV = (CVJ, PMR)\n"
    "KJQ = (TQF, HTS)\n"
    "CBB = (XRL, XSP)\n"
    "AAA = (QXT, CDL)\n"
    "RPS = (FXF, MQL)\n"
    "BPH = (VBF, FBJ)\n"
    "RQM = (GVB, RKD)\n"
    "KNQ = (MPV, DLX)\n"
    "XSS = (LBB, SVD)\n"
    "VXB = (MGQ, GCD)\n"
    "XBR = (JCG, LTM)\n"
    "HGR = (MFL, GGF)\n"
    "SJA = (KJB, VFS)\n"
    "CBL = (JFX, BBF)\n"
    "KXN = (XCL, VVG)\n"
    "FKV = (HGQ, TVS)\n"
    "HBS = (SSP, HPN)\n"
    "PTG = (GJC, TCN)\n"
    "DJG = (CSP, XCC)\n"
    "CNM = (JFS, FXR)\n"
    "KGD = (MXP, GFC)\n"
    "PMR = (SXV, RSK)\n"
    "RPR = (QLD, SBT)\n"
    "NFK = (DTC, NTR)\n"
    "JKH = (HSF, RXX)\n"
    "TXG = (VNS, PVQ)\n"
    "TRS = (MSQ, BRT)\n"
    "MLF = (PLL, LMX)\n"
    "CDD = (SHR, FKT)\n"
    "CQM = (KSF, FPN)\n"
    "KSL = (XPD, NMG)\n"
    "LBB = (TBB, RVJ)\n"
    "DQJ = (TNP, JLT)\n"
    "KLC = (KGC, BNK)\n"
    "CSL = (CVC, MVR)\n"
    "NCG = (JVS, JTD)\n"
    "JQL = (CBL, KCH)\n"
    "FBF = (FKV, DLC)\n"
    "JHM = (HMD, HCH)\n"
    "DGP = (BGB, JGR)\n"
    "SSH = (PHG, MVV)\n"
    "CSG = (QTP, TPG)\n"
    "KSF = (FPV, DKV)\n"
    "DJS = (PCC, RDN)\n"
    "XLB = (LKT, NCQ)\n"
    "XDS = (LNG, SLS)\n"
    "MFT = (KJT, LSH)\n"
    "STD = (PSS, JQH)\n"
    "LGM = (JMD, FLJ)\n"
    "GPR = (KGQ, FFB)\n"
    "KJT = (XRK, JPP)\n"
    "FQN = (KNQ, PNH)\n"
    "CRR = (KSR, DPR)\n"
    "RRD = (NCG, KKD)\n"
    "FLJ = (LNL, QPR)\n"
    "MQL = (SKC, BFB)\n"
    "FST = (XHS, QDN)\n"
    "DRT = (MQL, FXF)\n"
    "RDN = (HQB, HSD)\n"
    "SQH = (HTS, TQF)\n"
    "VBN = (BRD, TXB)\n"
    "CXV = (VMM, TXG)\n"
    "MSQ = (XSJ, BRG)\n"
    "PLL = (QSM, PCS)\n"
    "NTD = (PLN, GKV)\n"
    "GHP = (NCQ, LKT)\n"
    "CXG = (XGV, VVT)\n"
    "CPZ = (MVB, MKR)\n"
    "GSQ = (FXV, PPG)\n"
    "BCG = (LMQ, JMM)\n"
    "FMK = (RQD, QJG)\n"
    "CJQ = (BFV, XDS)\n"
    "DLC = (HGQ, TVS)\n"
    "LML = (JFC, DNN)\n"
    "XTC = (TDD, VPV)\n"
    "QHP = (SKP, CTC)\n"
    "TBB = (QBJ, KXQ)\n"
    "GPG = (VNX, DPZ)\n"
    "SSS = (CFM, HQK)\n"
    "DFJ = (MBV, RPX)\n"
    "DLX = (RGT, VSJ)\n"
    "KLL = (JKG, TPV)\n"
    "NKT = (GDK, LDD)\n"
    "GCH = (MLF, BFM)\n"
    "PPG = (BFJ, DCR)\n"
    "KHF = (HGD, MNX)\n"
    "SLK = (BXX, KBV)\n"
    "TDL = (FLP, DLB)\n"
    "GCS = (VPL, JVR)\n"
    "FPN = (DKV, FPV)\n"
    "NKL = (RCL, KQH)\n"
    "NHS = (FDJ, DXC)\n"
    "DHN = (RCK, KVD)\n"
    "QJG = (GPV, XQK)\n"
    "DKD = (MFB, PTB)\n"
    "FDJ = (HHQ, BJS)\n"
    "TPX = (GGF, MFL)\n"
    "JKG = (HBB, HLJ)\n"
    "BFV = (LNG, SLS)\n"
    "XTL = (LCS, XNT)\n"
    "NRM = (GNX, GKS)\n"
    "XSJ = (JCT, CDD)\n"
    "JXR = (CBL, KCH)\n"
    "TRV = (QDC, HNH)\n"
    "GXS = (MBV, RPX)\n"
    "HPN = (HVF, XRJ)\n"
    "SSD = (FST, NBJ)\n"
    "KGQ = (DMM, GKG)\n"
    "DDC = (XTQ, KVK)\n"
    "XHL = (MKR, MVB)\n"
    "HXD = (CGG, CGG)\n"
    "DSH = (BVJ, BJM)\n"
    "ZZZ = (CDL, QXT)\n"
    "LQL = (FVD, KLR)\n"
    "BNK = (VVN, BNP)\n"
    "PLD = (GJV, HDP)\n"
    "JCG = (TMP, CML)\n"
    "VTK = (KQN, JHS)\n"
    "MNX = (TTP, SVH)\n"
    "VTC = (DKN, HXM)\n"
    "JPP = (GPB, QHQ)\n"
    "HQK = (GGP, FMV)\n"
    "QDC = (MBB, FGH)\n"
    "QRD = (JML, VGV)\n"
    "SXV = (HGL, NGL)\n"
    "BRJ = (FKV, DLC)\n"
    "DCF = (PGX, VJK)\n"
    "BGF = (BQX, PMT)\n"
    "JML = (FXD, KTT)\n"
    "GFC = (JBN, KVS)\n"
    "FBB = (JQN, NQV)\n"
    "SKC = (CSG, RQJ)\n"
    "SLX = (NHS, JCS)\n"
    "QDN = (KHF, VXD)\n"
    "MBV = (DSC, RPD)\n"
    "DMM = (MVD, NHX)\n"
    "QMF = (CVM, HDJ)\n"
    "JCT = (SHR, FKT)\n"
    "RKL = (HNF, DKC)\n"
    "SMV = (RDK, RDK)\n"
    "TNP = (BHL, XNQ)\n"
    "XNQ = (JQL, JXR)\n"
    "GGF = (GDD, XTM)\n"
    "RQD = (XQK, GPV)\n"
    "LSJ = (BBC, PJS)\n"
    "KCR = (VCL, JVJ)\n"
    "KCH = (JFX, BBF)\n"
    "QRT = (BTX, KFQ)\n"
    "JCS = (FDJ, DXC)\n"
    "GVB = (PXL, NDD)\n"
    "BMC = (VNV, FSM)\n"
    "PCS = (QQT, NXG)\n"
    "BKQ = (QXV, DHP)\n"
    "GTN = (DTS, DXQ)\n"
    "KBV = (NBK, GSQ)\n"
    "GKS = (QLJ, DSH)\n"
    "MPG = (RMJ, DSM)\n"
    "GBB = (KQH, RCL)\n"
    "SGT = (CGG, MLZ)\n"
    "TCP = (JCG, LTM)\n"
    "RPD = (GNF, VFG)\n"
    "PCB = (GMV, MCN)\n"
    "GVX = (MRF, GXC)\n"
    "XGF = (KCR, CDF)\n"
    "PXS = (DLQ, DBS)\n"
    "GDK = (JKB, MJF)\n"
    "BPR = (TKH, DKD)\n"
    "PXL = (XTL, JPJ)\n"
    "CSP = (NRR, XDK)\n"
    "RSK = (NGL, HGL)\n"
    "BTX = (QBF, VPJ)\n"
    "XPD = (QRD, FQG)\n"
    "MJQ = (KQN, JHS)\n"
    "BLC = (TDD, VPV)\n"
    "TTP = (PTG, CQX)\n"
    "XSG = (GNV, DMT)\n"
    "NBJ = (QDN, XHS)\n"
    "KFQ = (VPJ, QBF)\n"
    "KNN = (XHL, CPZ)\n"
    "JVK = (XPJ, NRC)\n"
    "NRV = (MRD, VVM)\n"
    "DGC = (MRN, RKL)\n"
    "VMM = (VNS, PVQ)\n"
    "HFK = (QHX, MNT)\n"
    "SCQ = (VKL, XGR)\n"
    "BXA = (MKR, MVB)\n"
    "RDK = (LJP, GVX)\n"
    "KXM = (RCF, CQR)\n"
    "CMQ = (DJS, DHQ)\n"
    "VNS = (DDF, SSS)\n"
    "HJC = (CPM, CJM)\n"
    "VNX = (VPC, LVQ)\n"
    "DSM = (BSJ, GCS)\n"
    "TTT = (FBJ, VBF)\n"
    "LDN = (CVJ, PMR)\n"
    "JTD = (QMF, GXT)\n"
    "XSP = (BPR, SHS)\n"
    "QXT = (LVG, PLD)\n"
    "VFS = (XSS, CTN)\n"
    "TFK = (FLP, DLB)\n"
    "KLR = (FSQ, BNJ)\n"
    "GDG = (QQJ, HBN)\n"
    "QJK = (SHX, MCT)\n"
    "LKT = (TCJ, XLP)\n"
    "CMH = (VBB, GPG)\n"
    "JDV = (BQX, BQX)\n"
    "VPV = (SFH, BJD)\n"
    "GFM = (KXM, CPG)\n"
    "BDX = (LQX, QXJ)\n"
    "HGL = (VTS, QCT)\n"
    "GRN = (KJB, VFS)\n"
    "HNF = (HBC, NFK)\n"
    "VMN = (CJM, CPM)\n"
    "GPV = (JQQ, JVH)\n"
    "BCV = (RQM, FVV)\n"
    "SSG = (JKH, XMT)\n"
    "KBP = (FXR, JFS)\n"
    "VVT = (XVP, LSF)\n"
    "BPS = (BMK, JFK)\n"
    "BXJ = (DJG, JRH)\n"
    "VSS = (NBM, NLM)\n"
    "PMH = (FLJ, JMD)\n"
    "BSJ = (JVR, VPL)\n"
    "GPS = (BKR, TGN)\n"
    "BKM = (SLX, JCD)\n"
    "LMM = (GTB, CMD)\n"
    "KKP = (MJQ, VTK)\n"
    "NTG = (HXD, HXD)\n"
    "DHP = (DCD, BKM)\n"
    "XGP = (DBJ, PKP)\n"
    "GGP = (SCQ, QFS)\n"
    "NXR = (DSK, XGP)\n"
    "XNH = (BHP, SVB)\n"
    "HLN = (XSP, XRL)\n"
    "KJH = (SSH, QQC)\n"
    "QSM = (NXG, QQT)\n"
    "JHS = (PQH, CVR)\n"
    "RLK = (HNH, QDC)\n"
    "KGC = (VVN, BNP)\n"
    "BPK = (JFC, DNN)\n"
    "KJB = (CTN, XSS)\n"
    "VCL = (MPG, XCX)\n"
    "PKR = (NCG, KKD)\n"
    "NMG = (QRD, FQG)\n"
    "JVH = (HDK, NPX)\n"
    "NBM = (STN, PXS)\n"
    "MLX = (PNK, BCV)\n"
    "LVG = (HDP, GJV)\n"
    "DVN = (PTP, XGF)\n"
    "XDK = (SQS, VMQ)\n"
    "CVR = (GBB, NKL)\n"
    "SKV = (HMD, HCH)\n"
    "QTA = (HTQ, CLV)\n"
    "TPG = (KBP, CNM)\n"
    "VPL = (XVC, JCX)\n"
    "BKR = (BPS, PJD)\n"
    "NSP = (NBJ, FST)\n"
    "HBC = (NTR, DTC)\n"
    "TRB = (PLN, GKV)\n"
    "HDK = (KDG, FBC)\n"
    "CFM = (FMV, GGP)\n"
    "RPX = (RPD, DSC)\n"
    "HMD = (HVM, KKP)\n"
    "SXX = (SHX, MCT)\n"
    "QJV = (GRN, FPZ)\n"
    "DKC = (NFK, HBC)\n"
    "XCL = (MLD, CHG)\n"
    "XRJ = (LMV, QTK)\n"
    "HVM = (VTK, MJQ)\n"
    "VFG = (VTC, PVX)\n"
    "LQX = (NTG, NTG)\n"
    "KQD = (GCD, MGQ)\n"
    "PJD = (BMK, JFK)\n"
    "FKT = (JDN, CMH)\n"
    "BHL = (JXR, JQL)\n"
    "NLM = (PXS, STN)\n"
    "KDG = (XLB, GHP)\n"
    "NQV = (GDV, NKS)\n"
    "QDQ = (SJL, KGD)\n"
    "DTC = (QNG, PPK)\n"
    "QHQ = (KDJ, JPF)\n"
    "BBF = (THF, JVF)\n"
    "QQJ = (KJH, QDK)\n"
    "JFC = (GLL, TXF)\n"
    "KNX = (CVC, MVR)\n"
    "VBF = (TJM, GQJ)\n"
    "QQC = (MVV, PHG)\n"
    "FXF = (BFB, SKC)\n"
    "FPZ = (VFS, KJB)\n"
    "PNH = (DLX, MPV)\n"
    "TXB = (KCQ, QHP)\n"
    "TRL = (KSH, XJT)\n"
    "DKV = (MHK, JLV)\n"
    "MKR = (DRT, RPS)\n"
    "FPV = (MHK, JLV)\n"
    "SLV = (MNV, NTC)\n"
    "SRB = (GDN, CJQ)\n"
    "BMK = (BBT, TVP)\n"
    "NQK = (LQL, GCM)\n"
    "CDF = (VCL, JVJ)\n"
    "BBH = (SDD, GJR)\n"
    "DLB = (QDQ, FHL)\n"
    "XVC = (DXV, NXR)\n"
    "KFC = (RQK, TJJ)\n"
    "HDP = (MNM, HHJ)\n"
    "QDK = (QQC, SSH)\n"
    "JFS = (QHH, DVN)\n"
    "FXR = (QHH, DVN)\n"
    "TGN = (PJD, BPS)\n"
    "FFB = (DMM, GKG)\n"
    "DBK = (CJQ, GDN)\n"
    "RQK = (CXV, FHP)\n"
    "QTK = (PSM, RPR)\n"
    "JFX = (THF, JVF)\n"
    "HCA = (LJP, GVX)\n"
    "VVN = (CQM, JDK)\n"
    "CSH = (MBT, RHJ)\n"
    "HGC = (HXD, SGT)\n"
    "HNH = (MBB, FGH)\n"
    "QXJ = (NTG, HGC)\n"
    "PQH = (GBB, NKL)\n"
    "SVB = (KJQ, SQH)\n"
    "PPS = (BVL, KNN)\n"
    "MVD = (FSK, LSJ)\n"
    "CGG = (HTQ, CLV)\n"
    "KSH = (SMV, SMV)\n"
    "GNF = (VTC, PVX)\n"
    "QXV = (DCD, BKM)\n"
    "SPG = (NGG, MFT)\n"
    "XGR = (XTC, BLC)\n"
    "DPZ = (LVQ, VPC)\n"
    "JQN = (NKS, GDV)\n"
    "QQT = (NGP, CVV)\n"
    "TQF = (KXN, MKK)\n"
    "NHX = (FSK, LSJ)\n"
    "XLT = (GDK, LDD)\n"
    "KXC = (HJC, VMN)\n"
    "SVD = (TBB, RVJ)\n"
    "DXV = (DSK, XGP)\n"
    "TDD = (BJD, SFH)\n"
    "LMV = (PSM, RPR)\n"
    "BBT = (LGT, LGT)\n"
    "XLP = (FLX, RDG)\n"
    "DDF = (HQK, CFM)\n"
    "FSM = (BXJ, LXL)\n"
    "KHH = (SVL, RSF)\n"
    "SHR = (JDN, JDN)\n"
    "GLV = (MDV, LDN)\n"
    "MFB = (BSD, PGS)\n"
    "HGD = (TTP, SVH)\n"
    "KDJ = (NRV, FDM)\n"
    "DNN = (TXF, GLL)\n"
    "MFL = (XTM, GDD)\n"
    "VRB = (JPD, DPH)\n"
    "DLQ = (TNG, VBN)\n"
    "PPK = (BPK, LML)\n"
    "TPV = (HBB, HLJ)\n"
    "GMV = (QVH, KLC)\n"
    "VBB = (VNX, VNX)\n"
    "VVH = (QQJ, HBN)\n"
    "KTT = (BKS, XNH)\n"
    "JQH = (QRT, LGC)\n"
    "GNX = (QLJ, DSH)\n"
    "DTS = (FBF, BRJ)\n"
    "FTN = (DDC, NKN)\n"
    "JRH = (XCC, CSP)\n"
    "FFC = (NMG, XPD)\n"
    "HLK = (PRR, TRL)\n"
    "KRT = (LXC, NRM)\n"
    "JLT = (XNQ, BHL)\n"
    "HDJ = (KFN, CSH)\n"
    "DCN = (LQX, QXJ)\n"
    "MKK = (VVG, XCL)\n"
    "FXL = (SPG, XPN)\n"
    "TXF = (NSP, SSD)\n"
    "JKN = (FFB, KGQ)\n"
    "BJD = (GLV, XKH)\n"
    "XGL = (GPR, JKN)\n"
    "BJM = (DGP, BPN)\n"
    "JCB = (DPH, JPD)\n"
    "MLS = (DPF, XRH)\n"
    "JCX = (DXV, NXR)\n"
    "QLJ = (BVJ, BJM)\n"
    "LJD = (CRR, QCX)\n"
    "LCS = (JVK, GMN)\n"
    "HLD = (XGL, LLR)\n"
    "DSN = (GRN, GRN)\n"
    "JLV = (HLN, CBB)\n"
    "PMT = (DSN, QJV)\n"
    "HVF = (QTK, LMV)\n"
    "MNV = (KRD, BMC)\n"
    "LNS = (SLK, KTF)\n"
    "KKD = (JTD, JVS)\n"
    "QXG = (DTS, DXQ)\n"
    "QVH = (KGC, BNK)\n"
    "PLJ = (TSK, ZZZ)\n"
    "MRN = (HNF, DKC)\n"
    "JMM = (JDX, GVG)\n"
    "MHK = (CBB, HLN)\n"
    "THF = (LMT, DGC)\n"
    "TKH = (MFB, PTB)\n"
    "FCH = (BFM, MLF)\n"
    "HSF = (PHT, DSP)\n"
    "MNT = (DFS, KHH)\n"
    "GNR = (BKR, TGN)\n"
    "MNM = (FTC, FTN)\n"
    "BGB = (SXX, QJK)\n"
    "NGG = (KJT, LSH)\n"
    "HBN = (QDK, KJH)\n"
    "TVX = (PMH, LGM)\n"
    "GDV = (XNJ, BDQ)\n"
    "TJJ = (FHP, CXV)\n"
    "QCK = (JXV, NMT)\n"
    "XTK = (PKR, RRD)\n"
    "HHQ = (DBK, SRB)\n"
    "CPG = (CQR, RCF)\n"
    "XNJ = (LTK, KLL)\n"
    "LMQ = (JDX, GVG)\n"
    "DPR = (BQR, QFG)\n"
    "GXC = (BRR, CXG)\n"
    "CQR = (KNX, CSL)\n"
    "GJV = (MNM, HHJ)\n"
    "HTS = (KXN, MKK)\n"
    "RSF = (SSG, NNG)\n"
    "HCH = (HVM, KKP)\n"
    "RCL = (SQQ, VBL)\n"
    "NGL = (QCT, VTS)\n"
    "MCT = (GBN, DCF)\n"
    "QFS = (VKL, XGR)\n"
    "BNP = (CQM, JDK)\n"
    "BPN = (JGR, BGB)\n"
    "BRG = (JCT, CDD)\n"
    "PHN = (GNR, GPS)\n"
    "XBX = (TVX, FMG)\n"
    "PJS = (XCQ, PPS)\n"
    "SNF = (NTC, MNV)\n"
    "CLV = (TCP, XBR)\n"
    "CVJ = (RSK, SXV)\n"
    "NRC = (VRB, JCB)\n"
    "BFM = (PLL, LMX)\n"
    "GKG = (MVD, NHX)\n"
    "JPF = (FDM, NRV)\n"
    "GTB = (DFJ, GXS)\n"
    "DMT = (BKQ, GGM)\n"
    "DPH = (BCG, GFJ)\n"
    "MVB = (DRT, RPS)\n"
    "HTQ = (TCP, XBR)\n"
    "MJF = (XTK, GCB)\n"
    "GRG = (NLM, NBM)\n"
    "VKL = (BLC, XTC)\n"
    "NCV = (LXC, NRM)\n"
    "KTF = (KBV, BXX)\n"
    "KRD = (FSM, VNV)\n"
    "DBJ = (NQK, VSB)\n"
    "XCC = (NRR, XDK)\n"
    "XRK = (QHQ, GPB)\n"
    "PVR = (GDG, VVH)\n"
    "BSD = (GRG, VSS)\n"
    "PTP = (CDF, KCR)\n"
    "FDM = (VVM, MRD)\n"
    "BFB = (RQJ, CSG)\n"
    "PVX = (HXM, DKN)\n"
    "PHG = (DQJ, QVP)\n"
    "GMN = (XPJ, NRC)\n"
    "QPR = (JKT, QBG)\n"
    "CQX = (GJC, TCN)\n"
    "VTS = (HBS, LKG)\n"
    "BRT = (XSJ, BRG)\n"
    "LKG = (SSP, HPN)\n"
    "KVS = (BVN, TRS)\n"
    "NBK = (FXV, PPG)\n"
    "XGV = (XVP, LSF)\n"
    "SKP = (JHM, SKV)\n"
    "MPV = (VSJ, RGT)\n"
    "PNR = (XGL, LLR)\n"
    "BDQ = (KLL, LTK)\n"
    "JFK = (BBT, TVP)\n"
    "PCC = (HQB, HSD)\n"
    "TNL = (CMD, GTB)\n"
    "JMD = (QPR, LNL)\n"
    "FMV = (SCQ, QFS)\n"
    "LMX = (PCS, QSM)\n"
    "DXC = (BJS, HHQ)\n"
    "PXR = (QJG, RQD)\n"
    "FVV = (GVB, RKD)\n"
    "TSK = (QXT, CDL)\n"
    "QLD = (TPX, HGR)\n"
    "VPB = (JDV, BGF)\n"
    "GDN = (BFV, XDS)\n"
    "MLZ = (CLV, HTQ)\n"
    "XNM = (BCV, PNK)\n"
    "GXT = (CVM, HDJ)\n"
    "DPF = (XSG, RBT)\n"
    "DQQ = (GPC, KPF)\n"
    "BBC = (XCQ, XCQ)\n"
    "NXG = (NGP, CVV)\n"
    "RDG = (NKT, XLT)\n"
    "HHJ = (FTN, FTC)\n"
    "FTC = (DDC, NKN)\n"
    "RCK = (LBN, QCK)\n"
    "MGQ = (VMB, VPB)\n"
    "LGC = (BTX, KFQ)\n"
    "VHQ = (DMX, LJD)\n"
    "JKB = (XTK, GCB)\n"
    "DCR = (PVR, MGL)\n"
    "MRF = (CXG, BRR)\n"
    "XRL = (BPR, SHS)\n"
    "LBN = (JXV, NMT)\n"
    "MVV = (DQJ, QVP)\n"
    "HPH = (DHQ, DJS)\n"
    "FSP = (KXM, CPG)\n"
    "GPB = (KDJ, JPF)\n"
    "VGV = (KTT, FXD)\n"
    "MCN = (KLC, QVH)\n"
    "BNJ = (HMV, CVT)\n"
    "PKG = (RQK, TJJ)\n"
    "CCR = (PRR, TRL)\n"
    "NCQ = (TCJ, XLP)\n"
    "CHG = (PHN, XCG)\n"
    "HLJ = (CCR, HLK)\n"
    "VSJ = (LNS, LKP)\n"
    "SQS = (DCN, BDX)\n"
    "KFN = (MBT, RHJ)\n"
    "LGT = (JJQ, JJQ)\n"
    "MJM = (RDK, MTZ)\n"
    "LXL = (DJG, JRH)\n"
    "TMP = (PNX, PCB)\n"
    "KVD = (LBN, QCK)\n"
    "RQJ = (TPG, QTP)\n"
    "XTM = (RPK, FBB)\n"
    "LNG = (HPH, CMQ)\n"
    "PKP = (NQK, VSB)\n"
    "KGN = (LMM, TNL)\n"
    "QBG = (CFQ, KFV)\n"
    "NPX = (FBC, KDG)\n"
    "LXC = (GKS, GNX)\n"
    "LDD = (JKB, MJF)\n"
    "QCT = (HBS, LKG)\n"
    "KQN = (CVR, PQH)\n"
    "JVJ = (MPG, XCX)\n"
    "PLN = (PXP, DQQ)\n"
    "QNG = (LML, BPK)\n"
    "JGR = (QJK, SXX)\n"
    "HBX = (TNL, LMM)\n"
    "JJQ = (TSK, TSK)\n"
    "XJT = (SMV, MJM)\n"
    "BQX = (DSN, DSN)\n"
    "RVJ = (KXQ, QBJ)\n"
    "PHT = (XXV, DHN)\n"
    "BFJ = (PVR, MGL)\n"
    "BHP = (SQH, KJQ)\n"
    "TJM = (TXM, HFK)\n"
    "NMT = (HLD, PNR)\n"
    "DHQ = (PCC, RDN)\n"
    "PGS = (GRG, VSS)\n"
    "DSP = (XXV, DHN)\n"
    "MRD = (VXB, KQD)\n"
    "LKP = (KTF, SLK)\n"
    "FSQ = (CVT, HMV)\n"
    "VVG = (MLD, CHG)\n"
    "NGP = (NCD, PTT)\n"
    "NTC = (KRD, BMC)\n"
    "FHL = (SJL, KGD)\n"
    "BHV = (JJQ, PLJ)\n"
    "LJP = (MRF, GXC)\n"
    "SBT = (HGR, TPX)\n"
    "SVH = (CQX, PTG)\n"
    "MVX = (NVV, BBH)\n"
    "XCG = (GPS, GNR)\n"
    "RTC = (NVV, BBH)\n"
    "RGT = (LKP, LNS)\n"
    "HMV = (KRT, NCV)\n"
    "KCQ = (SKP, CTC)\n"
    "FVD = (FSQ, BNJ)\n"
    "QFG = (DMR, MLS)\n"
    "SHX = (DCF, GBN)\n"
    "DMR = (DPF, XRH)\n"
    "VMB = (JDV, BGF)\n"
    "TNG = (BRD, TXB)\n"
    "JDK = (FPN, KSF)\n"
    "GCB = (RRD, PKR)\n"
    "XCQ = (BVL, BVL)\n"
    "DBS = (TNG, VBN)\n"
    "FXD = (BKS, XNH)\n"
    "GQJ = (TXM, HFK)\n"
    "NVV = (GJR, SDD)\n"
    "MBB = (SNF, SLV)\n"
    "RMJ = (BSJ, GCS)\n"
    "JCD = (NHS, JCS)\n"
    "GBN = (VJK, PGX)\n"
    "VMQ = (DCN, BDX)\n"
    "HXM = (BPH, TTT)\n"
    "CDL = (LVG, PLD)\n"
    "DCD = (SLX, JCD)\n"
    "GNV = (GGM, BKQ)\n"
    "TCN = (KSL, FFC)\n"
    "SSP = (XRJ, HVF)\n"
    "PNX = (GMV, MCN)\n"
    "XCX = (DSM, RMJ)\n"
    "DMX = (CRR, QCX)\n"
    "GJC = (KSL, FFC)\n"
    "RKD = (PXL, NDD)\n"
    "FLP = (FHL, QDQ)\n"
    "PTT = (XMF, STD)\n"
    "TXM = (QHX, MNT)\n"
    "JVF = (DGC, LMT)\n"
    "NNG = (XMT, JKH)\n"
    "NKN = (KVK, XTQ)\n"
    "SLS = (CMQ, HPH)\n"
    "MGL = (GDG, VVH)\n"
    "VPC = (TKR, QNF)\n"
    "XMT = (RXX, HSF)\n"
    "QCX = (KSR, DPR)\n"
    "FBC = (XLB, GHP)\n"
    "CPM = (RTC, MVX)\n"
    "FGH = (SNF, SLV)\n"
    "SJL = (GFC, MXP)\n"
    "KVK = (FSP, GFM)\n"
    "VXD = (MNX, HGD)\n"
    "NDD = (XTL, JPJ)\n"
    "GJR = (NTD, TRB)\n"
    "LSH = (XRK, JPP)\n"
    "JQQ = (HDK, NPX)\n"
    "THS = (DMX, LJD)\n"
    "FSK = (BBC, PJS)\n"
    "PVQ = (DDF, SSS)\n"
    "RCF = (KNX, CSL)\n"
    "LMT = (MRN, RKL)\n"
    "HQB = (XNM, MLX)\n"
    "QHX = (KHH, DFS)\n"
    "GDD = (RPK, FBB)\n"
    "LLR = (JKN, GPR)\n"
    "XNT = (JVK, GMN)\n"
    "JBN = (BVN, TRS)\n"
    "MXP = (KVS, JBN)\n"
    "FXV = (DCR, BFJ)\n"
    "XQK = (JQQ, JVH)\n"
    "TVP = (LGT, BHV)\n"
    "GGM = (DHP, QXV)\n"
    "BKS = (BHP, SVB)\n"
    "DXQ = (FBF, BRJ)\n"
    "RXX = (DSP, PHT)\n"
    "GLL = (NSP, SSD)\n"
    "CTN = (SVD, LBB)\n"
    "NFX = (PNH, KNQ)\n"
    "DKN = (BPH, TTT)\n"
    "GFJ = (LMQ, JMM)\n"
    "XVP = (KXC, VPD)\n"
    "NCD = (XMF, STD)\n"
    "LVQ = (TKR, QNF)\n"
    "SDD = (TRB, NTD)\n"
    "VSB = (LQL, GCM)\n"
    "XMF = (JQH, PSS)\n"
    "HSD = (XNM, MLX)\n"
    "LDA = (VPC, LVQ)\n"
    "RBT = (DMT, GNV)\n"
    "NRR = (VMQ, SQS)\n"
    "LTK = (TPV, JKG)\n"
    "VBL = (RLK, TRV)\n"
    "GKV = (PXP, DQQ)\n"
    "JDN = (VBB, VBB)\n"
    "CML = (PCB, PNX)\n"
    "LNL = (QBG, JKT)\n"
    "SFH = (GLV, XKH)\n"
    "DFS = (RSF, SVL)\n"
    "FBJ = (GQJ, TJM)\n"
    "VPD = (HJC, VMN)\n"
    "STN = (DLQ, DBS)\n"
    "CVM = (CSH, KFN)\n"
    "MVR = (NFX, FQN)\n"
    "KFV = (TDL, TFK)\n"
    "JQV = (FMG, TVX)\n"
    "XPN = (MFT, NGG)\n"
    "TKR = (THS, VHQ)\n"
    "VPJ = (KFC, PKG)\n"
    "PTB = (BSD, PGS)\n"
    "PGX = (KGN, HBX)\n"
    "XRH = (RBT, XSG)\n"
    "QHH = (PTP, XGF)\n"
    "BJS = (DBK, SRB)\n"
    "KQH = (SQQ, VBL)\n"
    "LSF = (VPD, KXC)\n"
    "GVG = (JQV, XBX)\n"
    "BXX = (NBK, GSQ)\n"
    "JDX = (JQV, XBX)\n"
    "VNV = (BXJ, LXL)\n"
    "SVL = (NNG, SSG)\n"
    "MLD = (XCG, PHN)\n"
    "QNF = (THS, VHQ)\n"
    "PRR = (KSH, KSH)\n"
    "CFQ = (TDL, TFK)\n"
    "JVR = (JCX, XVC)\n"
    "CVV = (PTT, NCD)\n"
    "CJM = (RTC, MVX)\n"
    "XKH = (LDN, MDV)\n"
    "XHS = (KHF, VXD)\n"
    "MTZ = (GVX, LJP)\n"
    "BVJ = (DGP, BPN)\n"
    "VVM = (KQD, VXB)\n"
    "NTR = (PPK, QNG)\n"
    "FMG = (LGM, PMH)\n"
    "GPC = (GCH, FCH)\n"
    "RHJ = (GTN, QXG)\n"
    "JPD = (GFJ, BCG)\n"
    "PNK = (FVV, RQM)\n"
    "PFJ = (XPN, SPG)\n"
    "DSC = (VFG, GNF)\n"
    "PSM = (QLD, SBT)\n"
    "GCM = (FVD, KLR)\n"
    "CTC = (SKV, JHM)\n"
    "GCD = (VMB, VPB)\n"
    "TVS = (FXL, PFJ)\n"
    "BVN = (BRT, MSQ)\n"
    "FLX = (NKT, XLT)\n"
    "PXP = (KPF, GPC)\n"
    "QVP = (TNP, JLT)\n"
    "JXV = (HLD, PNR)\n"
    "SHS = (DKD, TKH)\n"
    "FHP = (TXG, VMM)\n"
    "BRR = (XGV, VVT)\n"
    "RPK = (JQN, NQV)\n"
    "NKS = (XNJ, BDQ)\n"
    "CVC = (NFX, FQN)\n"
    "PSS = (LGC, QRT)\n"
    "KSR = (BQR, QFG)\n"
    "FQG = (VGV, JML)\n"
    "QBF = (KFC, PKG)\n"
    "BVL = (XHL, XHL)\n"
    "JPJ = (LCS, XNT)\n"
    "TCJ = (FLX, RDG)\n"
    "BRD = (QHP, KCQ)\n"
    "XXV = (KVD, RCK)\n"
    "XPJ = (JCB, VRB)\n"
    "DSK = (DBJ, PKP)\n"
    "BQR = (MLS, DMR)\n"
    "HBB = (CCR, HLK)"
};

constexpr std::string_view example_input{
    "LR\n"
    "\n"
    "11A = (11B, XXX)\n"
    "11B = (XXX, 11Z)\n"
    "11Z = (11B, XXX)\n"
    "22A = (22B, XXX)\n"
    "22B = (22C, 22C)\n"
    "22C = (22Z, 22Z)\n"
    "22Z = (22B, 22B)\n"
    "XXX = (XXX, XXX)"
};

} // anonymous namespace

TEST(AdventOfCode, Day8Part1) {
    EXPECT_EQ(20221, AoC::day8_solution_part1(exercise_input));
}

TEST(AdventOfCode, Day8Part2) {
    EXPECT_EQ(14616363770447, AoC::day8_solution_part2(exercise_input));
}