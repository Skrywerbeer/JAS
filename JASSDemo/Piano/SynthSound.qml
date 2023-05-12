import JASSCore

Patchboard {
    id: root;
    property real frequency: 440;
//    output: SineOscillator {
//        offset: Constant {value: 0;}
////        amplitude: SineOscillator {
////            offset: Constant {value: 0.5}
////            amplitude: Constant {value: 0.5}
////            frequency: Constant {value: root.frequency/128}
////        }
////        frequency: Constant {value: root.frequency}
//        amplitude: Exponential {
//            timeConstant: Constant {value: 0.2;}

//        }

//        frequency: SineOscillator {
//            offset: Constant {value: root.frequency;}
//            amplitude: Constant {value: root.frequency*0.1;}
//            frequency: Constant {value: root.frequency*0.4;}
//        }

//    }
    output: Mixer {
        Decay {
            rate: 500;
            SquareOscillator {
                amplitude: SquareOscillator {
                    frequency: Constant {value: root.frequency*0.01;}
                    amplitude: Constant {value: 0.1;}
                    offset: Constant {value: 0.9;}
                }
                frequency: SineOscillator {
                    offset: Constant {value: root.frequency;}
                    amplitude: Constant {value: 5;}
                    frequency: Constant {value: root.frequency*0.01;}
                }
            }
        }
        Decay {
            rate: 400;
            TriangleOscillator {
                amplitude: SquareOscillator {
                    frequency: Constant {value: root.frequency*0.01;}
                    amplitude: Constant {value: 0.2;}
                    offset: Constant {value: 0.3;}
                }
                frequency: SineOscillator {
                    offset: Constant {value: 2*root.frequency;}
                    frequency: Constant {value: 20;}
                    amplitude: Constant {value: 5;}
                }
                slewRatio: Constant {value: 0.3;}
            }
        }
        Decay {
            rate: 200;
            TriangleOscillator {
                amplitude: SquareOscillator {
                    frequency: Constant {value: root.frequency*0.01;}
                    amplitude: Constant {value: 0.2}
                    offset: Constant {value: 0.4;}
                }
                frequency: SineOscillator {
                    offset: Constant {value: 3*root.frequency}
                    amplitude: Constant {value: 2;}
                    frequency: Constant {value: 30;}
                }
            }
        }
    }
}
