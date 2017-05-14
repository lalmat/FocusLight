<template>
    <div>
        <div id="port">
            FocusLight Port:
            <select v-model="cnxPort">
                <option v-for="p in cnxPortAry" :value="p">{{ p }}</option>
            </select>
            Status: [
              <span v-show="connected">Connected</span>
              <span v-show="!connected">Disconnected</span>
            ]
        </div>
        <input type="radio" name="color" v-model="color" value="R"> Rouge |
        <input type="radio" name="color" v-model="color" value="G"> Vert |
        <input type="radio" name="color" v-model="color" value="B"> Bleu |
        <input type="radio" name="color" v-model="color" value="L"> Bleu Faible |
        <input type="radio" name="color" v-model="color" value="Y"> Jaune |
        <input type="radio" name="color" v-model="color" value="M"> Magenta |
        <input type="radio" name="color" v-model="color" value="C"> Cyan |
        <input type="radio" name="color" v-model="color" value="W"> White |
        <input type="radio" name="color" v-model="color" value="O"> OFF
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
    }
    body {
        display: flex;
        align-items: center;
        justify-content: center;
        height: 100%;
        margin: auto;
    }
    #app {
        color: #2c3e50;
        max-width: 600px;
        font-family: Source Sans Pro, Helvetica, sans-serif;
        text-align: center;
    }
    #app a {
        color: #42b983;
        text-decoration: none;
    }
    #app p {
        text-align: justify;
    }
    .logo {
        width: auto;
        height: 100px;
    }
</style>
