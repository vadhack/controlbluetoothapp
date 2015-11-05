

var app = {
    macAddress: "98:D3:31:50:36:84",
    chars: "",


    initialize: function() {
        this.bindEvents();
    },

    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
        connectButton.addEventListener('touchend', app.manageConnection, false);
    },
    sendData: function(data){
        var success= function(){
            //app.display('Se envió datos correctamente.');
        }
        var failure= function(){
            //app.display('Error al enviar datos.');
        }
        bluetoothSerial.write(data, success, failure);
    },

    onDeviceReady: function() {
        init();
        var notEnabled = function() {
            app.display("Bluetooth está apagado. Enciendalo")
        }
        bluetoothSerial.isEnabled(
            function(){},
            notEnabled
        );
    },
    manageConnection: function() {

        var connect = function () {
            app.clear();
            app.display("Conectando... ");
            bluetoothSerial.connect(
                app.macAddress,  
                app.openPort,    
                app.showError   
            );
        };

        var disconnect = function () {
            app.display("Desconectando...");
            bluetoothSerial.disconnect(
                app.closePort,     
                app.showError   
            );
        };

        bluetoothSerial.isConnected(disconnect, connect);
    },

    openPort: function() {
        app.display("Conectado a : " + app.macAddress);
        connectButton.innerHTML = "Desconectar";
        bluetoothSerial.available(function (numBytes) {
            app.display("There are " + numBytes + " available to read.");
        }, function(){
            app.display('Error data available');
        });
        bluetoothSerial.subscribe('\n', function (data) {
            app.clear();
            procesarData(data);
        });
    },

    closePort: function() {
        app.display("Desconectado de : " + app.macAddress);
        connectButton.innerHTML = "Conectar";
        bluetoothSerial.unsubscribe(//desconecta de bluetooth
            function (data) {
                app.display(data);
            },
            app.showError
        );
    },

    showError: function(error) {
        app.display(error);
    },



    display: function(message) {
        display.innerHTML=message;
    },
    add: function(msg){
        display.innerHTML = display.innerHTML + msg;
    },
    clear: function() {
        var display = document.getElementById("message");
        display.innerHTML = "";
    }
};      

var splash =$('#splash')
    ,display = document.getElementById("message")
    ;

 

var irSeccion= function(sec){
    var secciones={
        login: $('#login'),
        menu: $('#menu'),
        crear: $('#crearuser')
    }
    for(seccion in secciones){
        if(seccion == sec) secciones[seccion].fadeIn(300);
        else secciones[seccion].fadeOut(1);
    }
}


var init= function(){
    app.manageConnection();
    setTimeout(function(){
        splash.fadeOut(1000);
        irSeccion('login');
    },2000);
}


var users=[
    {nombre: 'alvaro',pass: 'chato'},
    {nombre: 'jose', pass: 'perro'}
]

var newUserTemp={
    nombre:'',pass:''
}

var logear= function(){
    var user= document.getElementById('userIn');
    var pass= document.getElementById('passIn');
    if(user.value!==''&&pass.value!==''){
        app.sendData(user.value+'/');
        app.sendData(pass.value+'/');
        app.display('Esperando Arduino...');

        /*for(var i=0, l=users.length;i<l;i++){
            if(user.value==users[i].nombre && pass.value==users[i].pass) {
                app.display(' ');
                return irSeccion('menu');
                break;
            }else app.display('Usuario incorrecto');
        }*/
        
    }
}

var crearUser= function(){
    var user = document.getElementById('usercrearIn');
    var pass = document.getElementById('passcrearIn');
    if(user.value!==''&&pass.value!==''){
        
        for(var i=0, l=users.length;i<l;i++){
            if(user.value==users[i].nombre && pass.value==users[i].pass) {
                app.display('');
                return app.display('Ya existe Usuario');
                break;
            }
        }
        newUserTemp={nombre: user.value, pass: pass.value}; //guarda usuario en variable temporal hasta q se confirme que se guardò
        app.sendData(user.value+'*');
        app.sendData(pass.value+'*');
        app.display('Esperando Arduino...');
    }
}

var encenderLed= function(n){
    if(n==1) return app.sendData('led1on-');
    if(n==2) return app.sendData('led2on-');
}
var apagarLed= function(n){
    if(n==1) return app.sendData('led1off-');
    if(n==2) return app.sendData('led2off-');
}


var procesarData = function(data){
    switch(data){
        case 'loginok\n':
            app.display('Menu');
            irSeccion('menu');
            break;
        case 'loginerror\n':
            app.display('Error de autenticación');
            break;
        case 'crearok\n':
            users.push(newUserTemp);
            app.display('nuevo usuario Registrado: "'+newUserTemp.nombre+'"');
            newUserTemp={};
            irSeccion('menu');
            break;

        case 'led1on\n':
            app.display('Led 1 Encendido');
            break;
        case 'led1off\n':
            app.display('Led 1 Apagado');
            break;
        case 'led2on\n':
            app.display('Led 2 Encendido');
            break;
        case 'led2off\n':
            app.display('Led 2 Apagado');
            break;
        default:
            newUserTemp={};
            app.display('Arduino: '+data);
    }
}



