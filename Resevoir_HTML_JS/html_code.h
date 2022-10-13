// HTML code -----------------------------------------------------
const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Controlo de Reservatório</title>
</head>

<style>

    body {
        background-image: url('https://i.im.ge/2022/10/04/1fylYm.off.jpg');
        background-repeat: no-repeat;
        background-attachment: fixed;
        background-size: cover;
    }
    
    table {
        position: relative;
        width: 25%;
        border-spacing: 0px;
    }

    tr {
        border: 1px solid white;
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 20px;
        text-align: center;
    }

    th {
        text-align: center;
        height: 20px;
        font-family: "Consolas", "Montserrat", sans-serif;
        padding: 3px 3px;
        background-color: #cad5e0;
        color: #000000 !important;
    }

    td {
        height: 380px;
        padding: 3px 15px;
        vertical-align:bottom
    }

    .tabledata {
        font-size: 24px;
        position: relative;
        padding-left: 5px;
        padding-top: 5px;
        height: 10px;
        border-radius: 5px;
        color: #FFFFFF;
        line-height: 20px;
        transition: all 200ms ease-in-out;
        background-color: #317031;
    }

    .led_pwm_slider {
        -webkit-appearance: none;
        margin: 14px;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #363636;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
    }

    /* Mouse-over effects */
    .led_pwm_slider:hover {
        opacity: 1;
        /* Fully shown on mouse-over */
    }

    .led_pwm_slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #5c635d;
        cursor: pointer;
    }

    .led_pwm_slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #04AA6D;
        cursor: pointer;
    }

    .flex-container {
        display: flex;
        text-align: center;
    }

    .flex-child {
        flex: 1;
        border: 0px solid rgb(150, 150, 150);
    }

    .flex-child:first-child {
        margin-right: 800px;
    }

    .bodytext {
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 24px;
        text-align: center;
        font-weight: light;
        border-radius: 5px;
        display: inline;
        padding: 10px;
    }

    .navbar {
        width: 100%;
        height: 50px;
        margin: 0;
        padding: 10px 0px;
        background-color: #FFF;
        color: #000000;
        border-bottom: 5px solid #000000;
    }

    .navlogo {
        float: right;
        padding-right: 50px;
    }

    .fixed-top {
        position: fixed;
        top: 0;
        right: 0;
        left: 0;
        z-index: 1030;
    }

    .navtitle {
        float: left;
        height: 50px;
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 50px;
        font-weight: bold;
        line-height: 50px;
        padding-left: 20px;
    }

    .navheading {
        position: fixed;
        left: 60%;
        height: 50px;
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 20px;
        font-weight: bold;
        line-height: 20px;
        padding-right: 20px;
    }

    .navdata {
        justify-content: flex-end;
        position: fixed;
        left: 70%;
        height: 50px;
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 20px;
        font-weight: bold;
        line-height: 20px;
        padding-right: 20px;
    }

    .category {
        font-family: "Consolas", "Montserrat", sans-serif;
        font-weight: bold;
        font-size: 32px;
        line-height: 50px;
        padding: 20px 10px 0px 10px;
        color: #000000;
        text-align: left;
    }

    .heading {
        font-family: "Consolas", "Montserrat", sans-serif;
        font-weight: normal;
        font-size: 28px;
        text-align: center;
    }

    .btn {
        background-color: #444444;
        border: none;
        color: white;
        padding: 10px 25px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 10px 10px;
        cursor: pointer;
        border-radius: 10px;
    }

    .btn_input {
        background-color: #ff0000;
        border: none;
        color: white;
        padding: 25px 10px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 10px 10px;
        border-radius: 50px;
        width: 100px;
    }

    .foot {
        font-family: "Consolas", "Montserrat", sans-serif;
        font-size: 20px;
        position: fixed;
        bottom: 0;
        height: 30px;
        text-align: center;
        color: #000000;
        line-height: 20px;
        width: 100%;
    }

    .container {
        max-width: 1800px;
        margin: 0 auto;
    }

    table tr:first-child th:first-child {
        border-top-left-radius: 5px;
    }

    table tr:first-child th:last-child {
        border-top-right-radius: 5px;
    }

    table tr:last-child td:first-child {
        border-bottom-left-radius: 5px;
    }

    table tr:last-child td:last-child {
        border-bottom-right-radius: 5px;
    }

    hr {
        display: block;
        margin-top: 0.5em;
        margin-bottom: 0.5em;
        margin-left: auto;
        margin-right: auto;
        border-style: inset;
        border-width: 1px;
    }
</style>

<body style="background-color: #efefef" onload="process()">

    <header>
        <div class="navbar fixed-top">
            <div class="container">
                <div class="navtitle">Controlo de Reservatório</div>
                <div class="navlogo" id="logo"><img src="data:image/jpeg;base64,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" width="220"></div>

                <div class="navdata" id="date">mm/dd/yyyy</div>
                <br>
                <div class="navdata" id="time">00:00:00</div>
            </div>
        </div>
    </header>

    <main class="container" style="margin-top:70px">
 
        <div class="flex-container">
            <div class="flex-child magenta">
                <div class="category">Sensores de Nível</div>
                <br>
                <div class="bodytext">Nível Superior</div>
                <button type="button" class="btn_input" id="btn_input" disabled>Toggle</button>
                <br>
                <div class="bodytext">Nível Inferior</div>
                <button type="button" class="btn_input" id="btn_flash_input" disabled>Toggle</button>
                <br>
                <br>
                <hr>
                <br>
                <div class="category">Controlo de Saídas</div>
                <br>
                <div class="bodytext">Bomba de Enchimento</div>
                <button type="button" class="btn" id="btn0" onclick="ButtonPress0()">Toggle</button>
                <br>
                <div class="bodytext">Válvula de Entrada</div>
                <button type="button" class="btn" id="btn1" onclick="ButtonPress1()">Toggle</button>
                <br>
                <div class="bodytext">Válvula de Saída</div>
                <button type="button" class="btn" id="btn2" onclick="ButtonPress2()">Toggle</button>
                <br>
                <br>
                <hr>
                <br>
                <div class="category">Controlo RPM motor (PWM)</div>
                <br>
                <div class="bodytext">RPM Motor VFD</div>
                <br>
                <input type="range" class="led_pwm_slider" min="0" max="255" value="0" width="0%"
                    oninput="UpdateSlider(this.value)" />

            </div>
            <div class="flex-child green">
                <div class="category">Sensor Nível Analógico</div>
                <br>
                <div style="border-radius: 10px !important;">
                    <table>
                        <colgroup>
                        <tr>
                            <th>
                                <div class="heading">Nível [%]</div>
                            </th>   
                        </tr>
                        <tr>  
                            <td>
                                <div class="tabledata" id="b0"></div>
                            </td>                     
                        </tr>
                    </table>
                </div>
                <br>
            </div>
        </div>
    </main>
    <br>
    <br>
    <footer div class="foot" id="temp">Jorge Fernandes 104580 - Sistemas Flexíveis de Produção - Univ. Aveiro 2022</div>
    </footer>
</body>


<script type="text/javascript">

    // global variable visible to all java functions
    var xmlHttp = createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject() {
        if (window.XMLHttpRequest) {
            xmlHttp = new XMLHttpRequest();
        }
        else {
            xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress0() {
        var xhttp = new XMLHttpRequest();
        var message;
        // if you want to handle an immediate reply (like status from the ESP
        // handling of the button press use this code
        // since this button status from the ESP is in the main XML code
        // we don't need this
        // remember that if you want immediate processing feedback you must send it
        // in the ESP handling function and here
        /*
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            message = this.responseText;
            // update some HTML data
          }
        }
        */

        xhttp.open("PUT", "BUTTON_0", false);
        xhttp.send();
    }


    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress1() {
        var xhttp = new XMLHttpRequest();
        /*
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("button1").innerHTML = this.responseText;
          }
        }
        */
        xhttp.open("PUT", "BUTTON_1", false);
        xhttp.send();
    }

    function ButtonPress2() {
        var xhttp = new XMLHttpRequest();
        /*
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("button1").innerHTML = this.responseText;
          }
        }
        */
        xhttp.open("PUT", "BUTTON_2", false);
        xhttp.send();
    }

    function UpdateSlider(value) {
        var xhttp = new XMLHttpRequest();
        /*
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                // update the web based on reply from  ESP
                document.getElementById("pwm_led").innerHTML = this.responseText;
            }
        }
        */
        // this syntax is really weird the ? is a delimiter
        // first arg UPDATE_SLIDER is use in the .on method
        // server.on("/UPDATE_SLIDER", UpdateSlider);
        // then the second arg VALUE is use in the processing function
        // String t_state = server.arg("VALUE");
        // then + the controls value property
        xhttp.open("PUT", "UPDATE_SLIDER?VALUE=" + value, true);
        xhttp.send();
    }

    // function to handle the response from the ESP
    function response() {
        var message;
        var barheight;
        var currentsensor;
        var xmlResponse;
        var xmldoc;
        var dt = new Date();
        var color = "#e8e8e8";

        // get the xml stream
        xmlResponse = xmlHttp.responseXML;

        // get host date and time
        document.getElementById("time").innerHTML = dt.toLocaleTimeString();
        document.getElementById("date").innerHTML = dt.toLocaleDateString();

        // A0
        xmldoc = xmlResponse.getElementsByTagName("B0"); //bits for A0
        message = xmldoc[0].firstChild.nodeValue;

        if (message < 50) {
            color = "#8c0303";
        }
        else {
            color = "#139e38";
        }

        barheight = message;
        document.getElementById("b0").innerHTML = message;
        //document.getElementById("b0").style.width = (barheight + "%");
        document.getElementById("b0").style.height = (barheight + "%");
        // if you want to use global color set above in <style> section
        // otherwise uncomment and let the value dictate the color
        document.getElementById("b0").style.backgroundColor=color;
        //document.getElementById("b0").style.borderRadius="5px";

        /* xmldoc = xmlResponse.getElementsByTagName("V0"); //volts for A0
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("v0").innerHTML = message;
        document.getElementById("v0").style.width = (barheight + "%");
        // you can set color dynamically, maybe blue below a value, red above
        document.getElementById("v0").style.backgroundColor = color;
        //document.getElementById("v0").style.borderRadius="5px";
        */

        // button states
        xmldoc = xmlResponse.getElementsByTagName("BTN");
        message = xmldoc[0].firstChild.nodeValue;
        if (message == 0) {
            document.getElementById("btn_input").innerHTML = "OFF";
            document.getElementById("btn_input").style.background='#8c0303';
        }
        else {
            document.getElementById("btn_input").innerHTML = "ON ";
            document.getElementById("btn_input").style.background='#139e38';
        }

        xmldoc = xmlResponse.getElementsByTagName("BTN_FLASH");
        message = xmldoc[0].firstChild.nodeValue;
        if (message == 0) {
            document.getElementById("btn_flash_input").innerHTML = "OFF";
            document.getElementById("btn_flash_input").style.background='#8c0303';
        }
        else {
            document.getElementById("btn_flash_input").innerHTML = "ON ";
            document.getElementById("btn_flash_input").style.background='#139e38';
        }

        // LED states
        xmldoc = xmlResponse.getElementsByTagName("LED2");
        message = xmldoc[0].firstChild.nodeValue;
        if (message == 0) {
            document.getElementById("btn0").innerHTML = "DESLIGAR";
        }
        else {
            document.getElementById("btn0").innerHTML = "LIGAR";
        }

        xmldoc = xmlResponse.getElementsByTagName("LED13");
        message = xmldoc[0].firstChild.nodeValue;
        if (message == 0) {
            document.getElementById("btn1").innerHTML = "ABRIR";
        }
        else {
            document.getElementById("btn1").innerHTML = "FECHAR";
        }

        xmldoc = xmlResponse.getElementsByTagName("LED15");
        message = xmldoc[0].firstChild.nodeValue;
        if (message == 0) {
            document.getElementById("btn2").innerHTML = "ABRIR";
        }
        else {
            document.getElementById("btn2").innerHTML = "FECHAR";
        }
    }

    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process() {

        if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
            xmlHttp.open("PUT", "xml", true);
            xmlHttp.onreadystatechange = response;
            xmlHttp.send(null);
        }
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()", 100);
    }


</script>

</html>

)====="; 
// end of HTML code -----------------------------------------------------
