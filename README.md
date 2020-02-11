# A Geant4 template for radiation detector

This is a Geant4 template for developing simulation programs for radiation detectors. In this context, radiation is meant to be the radiations that one would encounter from various radioactive sources either natural or man-made.  The energy scake of focus is keV to a few MeV, and physics list is specialized to handle gamma, X-rays, electrons, positrons, protons, neutrons, charged ions. Other heavy hadrons are not included to reduce the program size and to speed up program execution.

For gamma rays, physics processes considered are mainly Compton and Rayleigh scattering, photoelectric effect and pair production. For electrons and positrons, multiple scattering, ionization and Bremsstrahlung are the main processes, and for positrons only annihilation. For protons and other charged nuclei, scattering, ionization and nuclear stopping are the main processes. For tritium (triton in Geant4) and generic ions, radioactive decay is also handled.



## USAGE OF THE PROGRAM



## HOW TO COMPILE



## AVAILABLE COMMANDLINE PARAMETERS

## ASCII OUTPUT


## USING THE MACROS

### VISUALIZATION
### GENERAL PARTICLE SOURCE
