import JASSCore

JASSPlayer {
    id: root

    function clearAll() {
        if (root.sources.length === 0)
            return
        for (let i = 0; i < root.sources.length; ++i)
            root.sources[i].destroy()
        root.sources = []
    }
    function initTestbed() {
        clearAll()
        var comp = Qt.createComponent("qrc:/composite/testBed.qml")
        for (let i = 0; i < 24; ++i) {
            root.sources.push(comp.createObject(root,
                                                {
                                                    frequency: Math.pow(2, i/12)*220,
                                                }
                                                )
                              )
        }
    }

    function initSines() {
        clearAll()
        var comp = Qt.createComponent("qrc:/composite/decaySine.qml")
        for (let i = 0; i < 24; ++i) {
            root.sources.push(comp.createObject(root,
                                                {
                                                    frequency: Math.pow(2, i/12)*220,
                                                    rate: Qt.binding(function() {return root.decayRate})
                                                }
                                                )
                              )
        }
    }
    function initSquares() {
        clearAll()
        var comp = Qt.createComponent("qrc:/composite/decaySquare.qml")
        for (let i = 0; i < 24; ++i) {
            root.sources.push(comp.createObject(root,
                                                {
                                                    frequency: Math.pow(2, i/12)*220,
                                                    rate: Qt.binding(function() {return root.decayRate}),
                                                    dutyCycle: Qt.binding(function() {return root.dutyCycle})
                                                }
                                                )
                              )
        }
    }
    function initTriangles() {
        clearAll()
        var comp = Qt.createComponent("qrc:/composite/decayTriangle.qml")
        for (let i = 0; i < 24; ++i) {
            root.sources.push(comp.createObject(root,
                                                {
                                                    frequency: Math.pow(2, i/12)*220,
                                                    rate: Qt.binding(function() {return root.decayRate}),
                                                    dutyCycle: Qt.binding(function() {return root.dutyCycle})
                                                }
                                                )
                              )
        }
    }

    property real dutyCycle: 0.5
    property int decayRate: 200
}
