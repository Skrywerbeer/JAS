# JASS
## Just Another Software Synthesizer
Trees are well suited for representing signal chains and QML is great for 
describing trees of objects. The added bonus is that the JASS easily interfaces
with the QML for the UI.

### Implmented Nodes
- Oscillators
- - Sine
- - Triangle
- - Square
- - Piecewise Linear
- - White Noise

- Functions
- - Exponential
- - Constant
- - Piecewise Linear

- Effects
- - Amplifier
- - Delay

### TODO
- MIDI interface types
- VST interface types
- Sequencer types
- Filter nodes
- File output
- Wider frames than mono


### Building

On linux with Qt6 installed.

```
git clone https://github.com/Skrywerbeer/JASS.git
cd JASS
cmake -B build
cmake --build build
```

Run `JASSDemo/JASSDemo` for a small set of examples.
