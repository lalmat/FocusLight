<template>
    <div class="viewport">
        <div id="port">
            <div class="selection">
                FocusLight Port:<br />
                <select v-model="cnxPort">
                    <option v-for="p in cnxPortAry" :value="p">{{ p }}</option>
                </select>
            </div>
            <span class="state">
            Status: [
              <span v-show="connected">Connected</span>
              <span v-show="!connected">Disconnected</span>
            ]
            </span>
        </div>
        <div class="colorList">
            R: <input type="number" min="0" max="255" v-model="Led_R"><br />
            G: <input type="number" min="0" max="255" v-model="Led_G"><br />
            B: <input type="number" min="0" max="255" v-model="Led_B"><br />
            <br />
            {{ color }}
        </div>
    </div>
</template>

<script>

    // With shell.openExternal(url) is how
    // external urls must be handled, not href
    const shell = require('electron').shell

    export default {
      data: function() {
        return {
          connected: false,
          message: 'Hello Vue!',
          cnxPort: '',
          cnxPortAry: [],
          cnxSP:null,
          Led_R:0,
          Led_G:0,
          Led_B:0,
        };
      },
      computed: {
        color: function() {
          return this.Led_R+";"+this.Led_G+";"+this.Led_B;
        }
      },
      watch: {
        'color' : function () {
          if (this.connected) {
            this.cnxSP.write(this.color);
          }
        },
        'cnxPort': function() {
          this.connect();
        }
      },
      mounted : function() {
        this.loadPorts();
      },
      methods: {
        loadPorts : function() {
          var v = this;
          SerialPort.list( function(err, ports) {
            for (var i=0; i<ports.length; i++) {
              if (ports[i].comName.indexOf("USB") > 0) {
                v.cnxPortAry.push(ports[i].comName);
              }
            }
          });
        },
        connect : function () {
          var v = this;
          this.cnxSP = new SerialPort(this.cnxPort, {baudRate: 115200}, function() {
            v.connected = true;
          });
        }
      }
    }
</script>

<style>
    html {
        height: 100%;
        font-family:sans-serif;
        font-size:0.85em;
    }
    body {
        height: 100%;
        margin: auto;
        overflow-x: hidden;
        overflow-y: hidden;
        background-color: #353535;
        color:#aaa;
    }
    #port {
        padding: 0.7em;
        width:100%

    }
    #port .selection select {
        width: 100%;
    }
    .viewport {
        width: 90%;
    }
    .colorItem label {
        padding: 0.5em;
        display: inline-block;
        width: 5em;
    }
    .colorList {
        margin-left: 0.7em;
        width: 100%;
    }
</style>
