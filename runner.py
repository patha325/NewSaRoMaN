import os
import math
import subprocess
import time
import sys
import random

class Runner:

    def __init__(self,in_numberOfEvents):
        self.numberOfEvents = in_numberOfEvents #10000
        self.FNULL = open(os.devnull, 'w')
        #self.seed = 1000*random.random()

    def make(self):
        outfile = open("make.log",'w')
        subprocess.call('cmake ..', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=outfile)
        subprocess.call('make', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=outfile)
        subprocess.call('make tests', shell=True, cwd = '/root/NewSaRoMaN/GenFit/build',stdout=outfile)
        outfile.close()
        
        
    def run(self):
        #Run genie for scintillator
        # http://minerva-docdb.fnal.gov/0034/003441/001/GENIE_tutorial-170309.pdf
        # -n, number of events
        # -r MC run number
        # -p PDG code
        # -t target PDG code
        # -e neutrino energy range
        # -f neutrino flux spectrum file

        self.seed = 1000*random.random()
        
        start = time.time()
        outfile = open("genie1.log",'w')
        command = './gevgen -r 14 -n '+str(self.numberOfEvents)+' -p 14 -t 1000060120[0.922582],1000010010[0.077418] -e 0.01,4.0 -f /root/NewSaRoMaN/data/nu_mu_decay_ND.root,numu_energy_n --seed '+str(self.seed)+' --event-generator-list CCQE --cross-sections /root/NewSaRoMaN/data/xsec_C12+H1_splines.xml'
        subprocess.call(command, shell=True, cwd = '/root/genie/bin',stdout=self.FNULL)#outfile)     
        outfile.close()
        subprocess.call('mv gntp.14.ghep.root /root/NewSaRoMaN/B4c/build/genie_active.root ', shell=True, cwd = '/root/genie/bin')
        elapsed = (time.time()-start)
        print 'Time to run Genie for Scintillator: %s seconds' % elapsed
        
        #Run genie for iron
        start = time.time()
        outfile = open("genie2.log",'w')
        command = './gevgen -r 14 -n '+str(self.numberOfEvents)+' -p 14 -t 1000260560 -e 0.01,4.0 -f /root/NewSaRoMaN/data/nu_mu_decay_ND.root,numu_energy_n --seed '+str(self.seed)+' --event-generator-list CCQE --cross-sections /root/NewSaRoMaN/data/xsec_Fe56_splines.xml'
        subprocess.call(command, shell=True, cwd = '/root/genie/bin',stdout=self.FNULL)#outfile) 
        outfile.close()
        subprocess.call('mv gntp.14.ghep.root /root/NewSaRoMaN/B4c/build/genie_passive.root ', shell=True, cwd = '/root/genie/bin')
        elapsed = (time.time()-start)
        print 'Time to run Genie for Iron: %s seconds' % elapsed
        
        #fix macro file for geant
        
        with open("/root/NewSaRoMaN/B4c/build/macro.mac", "w") as text_file:
            text_file.write("/run/initialize\n")
            text_file.write("/run/printProgress 10000\n")
            text_file.write("/run/beamOn %s" % self.numberOfEvents)
        
        #Geant
        start = time.time()
        subprocess.call('scp WAGASCI.gdml B4c/build', shell=True, cwd = '/root/NewSaRoMaN')
        outfile = open("geant.log",'w')
        subprocess.call('./exampleB4c -m macro.mac', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=self.FNULL)#outfile)
        outfile.close()
        subprocess.call('mv B4.root /root/NewSaRoMaN/GenFit/build/bin/in.root ', shell=True, cwd = '/root/NewSaRoMaN/B4c/build')
        elapsed = (time.time()-start)
        print 'Time to run Geant: %s seconds' % elapsed
        
        #Fitter
        start = time.time()
        subprocess.call('scp WAGASCI.gdml GenFit/build/bin', shell=True, cwd = '/root/NewSaRoMaN')
        outfile = open("GenFit.log",'w')
        subprocess.call('./measurementFactoryExample 0 '+str(self.numberOfEvents), shell=True, cwd = '/root/NewSaRoMaN/GenFit/build/bin',stdout=self.FNULL)#outfile)
        outfile.close()
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
