const char html_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Industrial IoT Monitor</title>

<style>
body{
  background:#0A0A0A;
  color:#52FF00;
  font-family:Consolas;
  text-align:center;
}

.normal{
  color:#52FF00;
}

.alta{
  color:#FF2D2D;
  font-weight:bold;
}

</style>
</head>

<body>

<h2>ESP 8266 SENAI</h2>

<h1>
<span id="TempValue" class="normal">0</span>&deg;C
</h1>

<div id="status" class="normal">NORMAL OPERATION</div>

<script>

function updateData(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState==4 && this.status==200){

      var temp = parseFloat(this.responseText);

      var tempSpan = document.getElementById("TempValue");
      var status = document.getElementById("status");

      tempSpan.innerHTML = temp.toFixed(1);

      if(temp > 29){
        status.innerHTML = "TEMPERATURA ALTA";
        status.className = "alta";
        tempSpan.className = "alta";
      }else{
        status.innerHTML = "NORMAL OPERATION";
        status.className = "normal";
        tempSpan.className = "normal";
      }
    }
  };
  xhttp.open("GET","/readTemp",true);
  xhttp.send();
}

setInterval(updateData,1000);
updateData();

</script>

</body>
</html>
)rawliteral";