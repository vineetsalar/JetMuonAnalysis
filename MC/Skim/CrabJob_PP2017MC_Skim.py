from WMCore.Configuration import Configuration
config = Configuration()
#subScript = "SuperSlimSkim.C"
subScript = "SuperSlimSkimMultipleFiles.C"
config.section_("General")
config.General.requestName = 'PP2017MC_SuperSlimSkim'
config.General.workArea = config.General.requestName 
config.General.transferLogs = False

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'runScript.sh'
config.JobType.scriptArgs = ['script='+subScript]
#config.JobType.inputFiles = ['FrameworkJobReport.xml',subScript,'jffcorr.tar.gz','testDataList.txt']
config.JobType.inputFiles = ['FrameworkJobReport.xml',subScript,'Spring18_ppRef5TeV_V2_MC_L2Relative_AK4PF.txt','JetCorrector.h']
config.JobType.outputFiles = ['PP_2017MC_5TeV_MC_Skim.root']
config.JobType.maxJobRuntimeMin = 1800

config.section_("Data")
config.Data.userInputFiles = open('FileList_pp2017MC.txt').readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.totalUnits = len(config.Data.userInputFiles)
config.Data.outLFNDirBase = '/store/user/kumarv/UICWork/MuonJetAna/Skims/PPMC/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8'
config.Data.publication = False
config.Data.ignoreLocality = True

config.section_("Site")
config.Site.whitelist = ['T2_US_*']
config.Site.storageSite = 'T2_US_Purdue'
#config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist = ['T2_CH_CERN']
#config.Site.whitelist = ['T2_US_Purdue']
#config.Site.storageSite = 'T2_CH_CERN'

config.Site.ignoreGlobalBlacklist = True

#"really" force crab to only run at whitelisted sites
config.section_("Debug")
config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
