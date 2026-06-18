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

.card{
  border:1px solid #52FF00;
  padding:20px;
  margin:20px auto;
  width:300px;
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

<h2>ESP8266 SENAI - Monitoramento</h2>

<div class="card">
  <h3>Temperatura</h3>
  <h1>
    <span id="TempValue" class="normal">0</span>&deg;C
  </h1>
  <div id="tempStatus" class="normal">NORMAL</div>
</div>

<div class="card">
  <h3>Distância</h3>
  <h1>
    <span id="DistValue" class="normal">0</span> cm
  </h1>
  <div id="distStatus" class="normal">NORMAL</div>
</div>

<script>

function updateTemp(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState==4 && this.status==200){

      var temp = parseFloat(this.responseText.trim());
      if(isNaN(temp)) return;

      var tempSpan = document.getElementById("TempValue");
      var status = document.getElementById("tempStatus");

      tempSpan.innerHTML = temp.toFixed(1);

      if(temp > 29){
        status.innerHTML = "TEMPERATURA ALTA";
        status.className = "alta";
        tempSpan.className = "alta";
      }else{
        status.innerHTML = "NORMAL";
        status.className = "normal";
        tempSpan.className = "normal";
      }
    }
  };
  xhttp.open("GET","/readTemp",true);
  xhttp.send();
}

function updateDist(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState==4 && this.status==200){

      var dist = parseFloat(this.responseText.trim());
      if(isNaN(dist)) return;

      var distSpan = document.getElementById("DistValue");
      var status = document.getElementById("distStatus");

      distSpan.innerHTML = dist.toFixed(0);

      if(dist < 10 && dist > 0){
        status.innerHTML = "OBJETO PRÓXIMO";
        status.className = "alta";
        distSpan.className = "alta";
      }else{
        status.innerHTML = "NORMAL";
        status.className = "normal";
        distSpan.className = "normal";
      }
    }
  };
  xhttp.open("GET","/readDist",true);
  xhttp.send();
}

function updateAll(){
  updateTemp();
  updateDist();
}

setInterval(updateAll,1000);
updateAll();

</script>

</body>
</html>
)rawliteral";