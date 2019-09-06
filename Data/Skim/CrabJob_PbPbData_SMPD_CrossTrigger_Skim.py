from WMCore.Configuration import Configuration
config = Configuration()
subScript = "SuperSlimSkimMultipleFiles.C"

config.section_("General")
config.General.requestName = 'PbPbData_SMPD_SuperSlimSkim_MuonJetTrigger'
config.General.workArea = config.General.requestName 
config.General.transferLogs = False

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'runScript.sh'
config.JobType.scriptArgs = ['script='+subScript]
#config.JobType.inputFiles = ['FrameworkJobReport.xml',subScript,'jffcorr.tar.gz','testDataList.txt']
config.JobType.inputFiles = ['FrameworkJobReport.xml',subScript,'Autumn18_HI_V4_DATA_L2Relative_AK4PF.txt','Autumn18_HI_V4_DATA_L2Residual_AK4PF.txt','JetCorrector.h']
config.JobType.outputFiles = ['PbPb_5TeV_SingleMuPD_MuJetTrigger.root']
config.JobType.maxJobRuntimeMin = 1800

config.section_("Data")
#config.Data.userInputFiles = open('list_PbPb_Data.txt').readlines()
#config.Data.userInputFiles = open('DataFileListPtHat30.txt').readlines()
#config.Data.userInputFiles = open('testDataList.txt').readlines()
config.Data.userInputFiles = open('PbPb2018Data_SingleMuon_HLT_HIL3Mu3_PuAK4CaloJet60_Aug19.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.totalUnits = len(config.Data.userInputFiles)
config.Data.outLFNDirBase = '/store/user/kumarv/UICWork/MuonJetAna/Skims/PbPb2018DataSMPDMuonJetTrigger'
config.Data.publication = False
config.Data.ignoreLocality = True

config.section_("Site")
config.Site.whitelist = ['T2_US_*']
config.Site.storageSite = 'T2_US_Purdue'
#config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist = ['T2_CH_CERN']
#config.Site.storageSite = 'T2_CH_CERN'
config.Site.ignoreGlobalBlacklist = True

#"really" force crab to only run at whitelisted sites
config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
