import JASSCore

PatchBoard {
    id: root;
    property alias frequency: baseOsc.frequency;
    output: Mixer {
        Decay {
            rate: 800;
                VCA {
                    cv: Decay {
                        rate: 100;
                        SineOscillator {
                            frequency: baseOsc.frequency*0.01;
                            amplitude: 0.3
                            offset: amplitude;
                        }
                    }
                    input: Mixer {
                        TriangleOscillator {id: baseOsc; slewRatio: 0.3;}
                        SineOscillator {frequency: baseOsc.frequency; amplitude: 0.3}
                    }
                }
        }
    }
}
