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
            <div class="colorItem" v-for="c in colorAry" :style="{'background-color':c.color}">
                <span class="colorDot" :style="{'background-color':c.color}">
                  <input :id="c.id" type="radio" name="color" v-model="color" :value="c.id">
                </span>
                <label :for="c.id">{{ c.text }}</label>
            </div>
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
          color: "",
          message: 'Hello Vue!',
          cnxPort: '',
          cnxPortAry: [],
          cnxSP:null,
          colorAry : [
            {id:'R', color:'#FF0000', text:'Red'},
            {id:'G', color:'#00FF00', text:'Green'},
            {id:'B', color:'#0000FF', text:'Blue'},
            {id:'L', color:'#000077', text:'DarkBlue'},
            {id:'Y', color:'#00FF00', text:'Green'},
            {id:'M', color:'#FF00FF', text:'Magenta'},
            {id:'C', color:'#00FFFF', text:'Cyan'},
            {id:'W', color:'#FFFFFF', text:'White'},
            {id:'O', color:'#000000', text:'OFF'}
          ]
        };
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
          this.cnxSP = new SerialPort(this.cnxPort, null, function() {
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
