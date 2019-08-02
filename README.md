# Micromouse 2019
UT RAS Micromouse repository for 2019

The repository is structured with hardware eagle files under the [pcb](./pcb) directory and the esp-idf projects under the [software/test-programs](./software/test-programs) directory. To make or flash a program move into a project folder corresponding to that program and run either `make` or `make flash` respectively.
## Setup Software
- Download and Install esp-idf which can be found [here](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/#setting-up-development-environment)
- Download and build software
```bash
git clone https://github.com/ut-ras/mm19
cd software
make
``` 
