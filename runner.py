import os
import math
import subprocess
import time

numberOfEvents = 1000

#Run genie for scintillator
start = time.time()
outfile = open("genie1.log",'w+')
command = './gevgen -r 14 -n '+str(numberOfEvents)+' -p 14 -t 1000060120[0.922582],1000010010[0.077418] -e 0.01,4.0 -f /root/NewSaRoMaN/data/nu_mu_decay_ND.root,numu_energy_n --seed 14 --event-generator-list CCQE --cross-sections /root/NewSaRoMaN/data/xsec_C12+H1_splines.xml'
subprocess.call(command, shell=True, cwd = '/root/genie/bin',stdout=outfile)     
outfile.close()
subprocess.call('mv gntp.14.ghep.root /root/NewSaRoMaN/B4c/build/genie_active.root ', shell=True, cwd = '/root/genie/bin')
elapsed = (time.time()-start)
print 'Time to run process: %s seconds' % elapsed

#Run genie for iron
start = time.time()
outfile = open("genie2.log",'w+')
command = './gevgen -r 14 -n '+str(numberOfEvents)+' -p 14 -t 1000260560 -e 0.01,4.0 -f /root/NewSaRoMaN/data/nu_mu_decay_ND.root,numu_energy_n --seed 14 --event-generator-list CCQE --cross-sections /root/NewSaRoMaN/data/xsec_Fe56_splines.xml'
subprocess.call(command, shell=True, cwd = '/root/genie/bin',stdout=outfile) 
outfile.close()
subprocess.call('mv gntp.14.ghep.root /root/NewSaRoMaN/B4c/build/genie_passive.root ', shell=True, cwd = '/root/genie/bin')
elapsed = (time.time()-start)
print 'Time to run process: %s seconds' % elapsed

#fix macro file for geant

with open("/root/NewSaRoMaN/B4c/build/macro.mac", "w") as text_file:
    text_file.write("/run/initialize\n")
    text_file.write("/run/printProgress 100\n")
    text_file.write("/run/beamOn %s" % numberOfEvents)

#Geant
start = time.time()
outfile = open("geant.log",'w+')
subprocess.call('./exampleB4c -m macro.mac', shell=True, cwd = '/root/NewSaRoMaN/B4c/build',stdout=outfile)
outfile.close()
elapsed = (time.time()-start)
print 'Time to run process: %s seconds' % elapsed
