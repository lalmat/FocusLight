// Basic init
const electron = require('electron')
const {app, BrowserWindow} = electron

// Let electron reloads by itself when webpack watches changes in ./app/
require('electron-reload')(__dirname, {
	electron: require('${__dirname}/../../node_modules/electron')
})

// To avoid being garbage collected
let mainWindow

app.on('ready', () => {

    let mainWindow = new BrowserWindow({width: 800, height: 600})

    mainWindow.loadURL(`file://${__dirname}/app/index.html`)

})
