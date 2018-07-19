import os
import math
import subprocess
import time
import sys
import random

class Runner:

    def __init__(self,in_numberOfEvents):
        self.MCrunNumber = 14 #Number for generating the name of the genie file. Random number.
        self.numberOfEvents = in_numberOfEvents #10000
        self.FNULL = open(os.devnull, 'w')
        self.seed = 1000*random.random()
        self.pdg = 14 #PDG number for genie generation, 14 numu, -14 numubar
        self.neutrinoMode = 1 #1 or 0, lets Geant know to handle neutrinos
        self.eSpectrum = 0 # 1 or 0, tells Geant in single particle mode (neutrino 0) to run espectrum else eFix.
        self.eMin = 0.1 #GeV
        self.eMax = 4.0 #GeV
        self.eFix = 2.0 #GeV
        self.vertexPos = -3000 #mm, position for single particle beam
        self.particle = "mu-" #particle for single particle beam
        self.region = "TASD" #"SFFFS0" #region for neutrino interaction. //"SFFFS0";//"TASD";//"WAGASCIDetectorMod";//"PASSIVE";//"ACTIVE","TASD"
        self.geomFileG = "../../MINDnew_aida.gdml" #relative path from geant to geometry file.
        self.geomFileF = "../../../MINDnew_aida.gdml" #relative path from Genfit to geometry file.
        self.energyRange =str(self.eMin)+','+str(self.eMax)
        self.NuStorm = True
        self.skipTASD = 0 #adds TASD skipping for fitter.
        self.fluxfile = "/root/NewSaRoMaN/data/nu_mu_decay_ND.root"
        self.histoname = "numu_energy_n"
        self.eventtype = "CCQE"
        self.scintCode = "1000060120[0.922582],1000010010[0.077418]"
        self.ironCode = "1000260560"
        self.scintXSec = "/root/NewSaRoMaN/data/xsec_C12+H1_splines.xml"
        self.ironXSec = "/root/NewSaRoMaN/data/xsec_Fe56_splines.xml"

        if not self.NuStorm:
            self.fluxfile = "/root/NewSaRoMaN/data/T2KRHCmodeflux.root"
            if self.pdg==14:
                self.histoname = "hist_nu"
            else:
                self.histoname = "hist_nubar"

    def runGenie(self,targetCodeStr,targetXSecStr):
        # https://arxiv.org/abs/1510.05494v1
        # http://minerva-docdb.fnal.gov/0034/003441/001/GENIE_tutorial-170309.pdf
        # -n, number of events
        # -r MC run number
        # -p PDG code
        # -t target PDG code
        # -e neutrino energy range
        # -f neutrino flux spectrum file
        # -w Forces generation of weighted events.
        start = time.time()


        command = ['./gevgen','-r',str(self.MCrunNumber),'-n',str(self.numberOfEvents),'-p',str(self.pdg),'-t',targetCodeStr,
                   '-e',self.energyRange,'-f',self.fluxfile+','+self.histoname,'--seed',str(self.seed),
                   '--event-generator-list',self.eventtype,'--cross-sections',targetXSecStr,'-w']

        print subprocess.list2cmdline(command)
        subprocess.call(subprocess.list2cmdline(command), shell=True, cwd = '/root/genie/bin',stdout=self.FNULL)
        elapsed = (time.time()-start)
        print 'Time to run Genie for %s: %s seconds' % (targetCodeStr,elapsed)

        
    def make(self):
        outfile = open("make.log",'w')
        subprocess.call('cmake ..', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=outfile)
        subprocess.call('make', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=outfile)
        subprocess.call('cmake ..',shell=True, cwd = '/root/NewSaRoMaN/GenFit/build',stdout=outfile)
        subprocess.call('make tests', shell=True, cwd = '/root/NewSaRoMaN/GenFit/build',stdout=outfile)
        outfile.close()
        
        
    def run(self):
        #Run genie for scintillator

        if(self.neutrinoMode):
            self.runGenie(self.scintCode,self.scintXSec)
            subprocess.call('mv gntp.'+str(self.MCrunNumber)+'.ghep.root /root/NewSaRoMaN/B4c/build/genie_active.root ', shell=True, cwd = '/root/genie/bin')
            #Run genie for iron
            self.runGenie(self.ironCode,self.ironXSec)
            subprocess.call('mv gntp.'+str(self.MCrunNumber)+'.ghep.root /root/NewSaRoMaN/B4c/build/genie_passive.root ', shell=True, cwd = '/root/genie/bin')
        
        #write macro file for geant
        
        with open("/root/NewSaRoMaN/B4c/build/macro.mac", "w") as text_file:
            text_file.write("/run/initialize\n")
            text_file.write("/run/printProgress 10000\n") #random high number
            text_file.write("/run/beamOn %s" % self.numberOfEvents)

        #write config file for geant
        eMin = 1000 * self.eMin  #need to be in MeV
        eMax = 1000 * self.eMax  #need to be in MeV
        eFix = 1000 * self.eFix  #need to be in MeV
        with open("/root/NewSaRoMaN/B4c/build/config.file", "w") as text_file:
            text_file.write("neutrino %s\n" % self.neutrinoMode)
            text_file.write("eSpectrum %s\n" % self.eSpectrum)
            text_file.write("eMin %s\n" % eMin) #need to be in MeV
            text_file.write("eMax %s\n" % eMax)
            text_file.write("eFix %s\n" % eFix)
            text_file.write("VertexPosZ %s\n" % self.vertexPos)
            text_file.write("particle %s\n" % self.particle)
            text_file.write("region %s\n" % self.region)
            text_file.write("geom %s" % self.geomFileG)
        
        
        #Geant
        start = time.time()
        print 'Starting at %s' % time.ctime()
        subprocess.call('scp WAGASCI.gdml B4c/build', shell=True, cwd = '/root/NewSaRoMaN')
        #outfile = open("geant.log",'w')
        subprocess.call('./exampleB4c -m macro.mac', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=self.FNULL)#outfile)
        #outfile.close()
        subprocess.call('mv B4.root /root/NewSaRoMaN/GenFit/build/bin/in.root ', shell=True, cwd = '/root/NewSaRoMaN/B4c/build')
        elapsed = (time.time()-start)
        print 'Time to run Geant: %s seconds' % elapsed
        
        
        #Fitter
        start = time.time()
        print 'Starting at %s' % time.ctime()
        subprocess.call('scp WAGASCI.gdml GenFit/build/bin', shell=True, cwd = '/root/NewSaRoMaN')
        #outfile = open("GenFit.log",'w')
        subprocess.call('./measurementFactoryExample 0 '+str(self.numberOfEvents)+' '+str(self.skipTASD)+' '+self.geomFileF, shell=True, cwd = '/root/NewSaRoMaN/GenFit/build/bin',stdout=self.FNULL, stderr=self.FNULL)#outfile)
        #outfile.close()
        subprocess.call('mv out.root ../../../recOut.root', shell=True, cwd = '/root/NewSaRoMaN/GenFit/build/bin')
        subprocess.call('mv in.root ../../../simOut.root', shell=True, cwd = '/root/NewSaRoMaN/GenFit/build/bin')
        elapsed = (time.time()-start)
        print 'Time to run GenFit: %s seconds' % elapsed

#######################################################################################################################
#File specific functions
#######################################################################################################################


if __name__ == "__main__":
    run = Runner(sys.argv[1])
    run.run()
    #run.make()
