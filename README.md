## Example G4 simulation code for Dr. Febbraro's setup

Basic setup for currently non-existent geometry to record hits of optical photons.

### Currently on the package:

- PMT Hit class which can be expanded to include hit position, time, energy....
- Optical photon particle gun with random polarization/momentum direction.
- Very basic format to save ROOT histograms with number of photons hitting PMT or absorbed.
- Tracking classes to manually record hits.
- Messenger classes for particle gun/event settings/tracking actions.


```markdown
Syntax highlighted code block

# To run the code (Assuming G4 already installed):
1. Clone repository locally.
2. Make "Build directory".
3. cmake <path-to-cloned-repository>
4. make -j<number of processors>


**Bold** and _Italic_ and `Code` text

```
