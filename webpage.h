 // convert the received string in to numbers line 339
 // min max line 90
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = R"=="==( 
<?xml version='1.0' encoding='utf-8'?>
<!DOCTYPE html PUBLIC '-//w3c//dtd xhtml 1.0 strict//en' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml'>
  <head>
    <!-- <meta http-equiv='refresh' content='1'><!--  auto update time : 1s -->
    <meta content='text/html;charset=utf-8' http-equiv='Content-Type'>
    <title>
      Couveuse
    </title>
      
    <style>
      body           { background-color : lightgrey; font-size: 100% }
      #wrapper       { width: 500px; margin: 10px auto;  padding: 5px 5px 5px 5px; text-align:center; border: 2px solid blue; border-radius: 15px;  }
      h2             { text-align: center;}
      h3             { margin: 0px 0px 5px 0px; }
      
      #topContainer  { display: flex; align-items: center;  justify-content: center; Margin: 0px auto 1em auto;}
      #topContainer2 { text-align: center;  margin-right: 1em; }
      #time          { display: inline; font-family: 'Courier New', Courier, monospace; font-size: 200%; }
      #date          { display: inline; font-family: 'Courier New', Courier, monospace; font-size: 200%; }
      
      #dialContainer { display:inline-block; margin: 0px auto 0px auto; }
      #dial_1        { display:inline-block; }
      #dial_2        { display:inline-block; margin: 0px 0px 0px 30px; }
      canvas         { background-color: #ffffff; }
      .bigText       { font-size: 150%;}  
      .noMargin      { margin: 0px 0px 0px 0px; }
      
      #graphContainer { display:inline-block;  text-align:left; margin: 10px 0px 10px 0px;  }
      #key            { width: 500px;  text-align:center;} 
    </style>
      
  </head>
    <body >
      <div id='wrapper'>
        <h1>Temperature & Humidity</h1>
  
        <div id='topContainer'>
          <p>
            <span id='date'>00:00:00</span>
            <span>&emsp;</span>
            <span id='time'>00:00:00</span>
          </p>          
        </div>

        <div id='dialContainer'> 
          <div id='dial_1'> 
            <h3>Temperature</h3>
            <canvas id='canvasTemp' width='200' height='150'  style='border:1px solid #000000;' > </canvas>
            <p class='noMargin bigText'><span id='temp'>0.0</span> °C</p>
          </div>    
  
          <div id='dial_2'> 
            <h3>Humidity</h3>
            <canvas id='canvasHumid' width='200' height='150'  style='border:1px solid #000000;' > </canvas>
            <p class='noMargin bigText'><span id='humd'>0</span> %</p>
          </div>
        </div>  <!--  'dialContainer'  -->
       
        <div id='graphContainer'> 
          <canvas id='grahp' width='440' height='150'  style='border:1px solid #000000; background-color:white;' > </canvas> 
        </div>
        <div id='key'>
          <p>
            <span style='color:red;font-weight:bold'>Temp</span>
            &emsp;*&ensp;*&ensp;*&emsp;
            <span style='color:blue;font-weight:bold'>Hum</span>
            &emsp;*&ensp;*&ensp;*&emsp;
            <span style='font-weight:bold'>20 x 5 mins</span>
            &emsp;*&ensp;*&ensp;*&emsp;
            <span id='cpt'style='font-weight:bold'>0</span>
          </p>
        </div>  
      
      </div> <!--  'wrapper'  -->
    </body>
  
  <script type='text/javascript'>
  // <![CDATA[
  
  function updateValues(h,t,b, tempArray, humdArray, cpt)
  {
    var interstepT = 1;
    var interstepH = 2;
//  function drawDial(canvasID, dialColour, startAngle, stopAngle, minVal, maxVal, dialValue)    
    drawDial('canvasTemp',  '#ffaaaa', 160, 20, 20,  50, t, interstepT); 
    drawDial('canvasHumid', '#aaaaff', 160, 20, 20, 100, h, interstepH);
    document.getElementById('temp').innerHTML = t;
    document.getElementById('humd').innerHTML = h;
    document.getElementById('cpt').innerHTML = cpt;

    //var graphCanvas = 'grahp';
    var graphMin = 20;
    var graphMax = 100;
    var drawLines = true;
    var drawinterLines = true;    
//  function drawGraph(canvasID, gMin, gMax, drawLines, t,h, tempArray, humdArray)    
    drawGraph('grahp', graphMin, graphMax, drawLines, t, h, tempArray, humdArray);
  }
    
  // ===========================================  DIAL  =========================================
  
  function drawDial(canvasID, dialColour, startAngle, stopAngle, minVal, maxVal, dialValue, step)
  {
    oneDegreeInRadians = Math.PI/180;
    if (stopAngle < startAngle) { stopAngle = stopAngle + 360;}

    let arcStartAngleInRadians =  oneDegreeInRadians * (startAngle-5)  ;
    let arcStopAngleInRadians  =  oneDegreeInRadians * (stopAngle+5) ;  

    var c = document.getElementById(canvasID);
    var ctx = c.getContext('2d');
    ctx.clearRect(0, 0, c.width, c.height);
    ctx.save();
    
    let H = c.height;
    let W = c.width;
    
    let arcLineWidth = W/5;
    ctx.translate(W/2, W/2);        // move coordinates 0,0 to the centre of the canvas
    
    // draw arc
    ctx.beginPath();
    let radius = W/2 - (arcLineWidth/2) - (W/100);      
    ctx.lineWidth = arcLineWidth;
    ctx.lineCap = 'butt';
    ctx.strokeStyle = dialColour;
    ctx.arc(0, 0, radius, arcStartAngleInRadians, arcStopAngleInRadians, false);
    ctx.stroke();
    
    // draw centre circle
    ctx.beginPath();
    let centerCircleRadius = W/100*3.5
    ctx.strokeStyle = '#000000';
    ctx.fillStyle = '#222222';
    ctx.lineWidth = 2;
    ctx.arc(0, 0, centerCircleRadius, 0, 2 * Math.PI, true);
    ctx.stroke();
    ctx.fill();   

    // draw ticks 
    ctx.beginPath();
    ctx.lineWidth = 1;
    ctx.lineCap = 'butt';
    ctx.strokeStyle = '#333333';
  
    ctx.font = '12px Arial';
    ctx.fillStyle = '#333333';
    ctx.textAlign = 'center'; 
    ctx.textBaseline = 'top'; 

    let tickStartPoint = radius - (arcLineWidth/2) ;   // bottom of the arc
    let tickLength =  5/8 * arcLineWidth - 5;
    
    let labelPos = radius + (arcLineWidth/2) - 2; 

    for (let angle=minVal; angle<=maxVal; angle = (angle + (5 * step)))
    {   
      let angleInDegrees =  (angle-minVal) *  ((stopAngle - startAngle) / (maxVal - minVal)) + startAngle  ;
      let angleInRadians = angleInDegrees * oneDegreeInRadians;

      ctx.rotate(angleInRadians );  
      ctx.moveTo(tickStartPoint, 0 );                   
      ctx.lineTo(tickStartPoint + tickLength, 0 );
      ctx.stroke();
            
      // draw the label at the right angle.
      // rotate the dial - 90 degree, draw the text at the new top of the dial, then rotate +90.
      // this means we use the - y axis.
      
      ctx.rotate(90*oneDegreeInRadians); 
      ctx.fillText(angle.toString(), 0, -labelPos );        
      ctx.rotate(-90*oneDegreeInRadians); 
      
      ctx.rotate(-angleInRadians);  //  this puts the dial back where it was.     
    }
// ****************************************************************** 
    for (let angle=minVal; angle<=maxVal; angle = angle + step)
    {   
      let angleInDegrees =  (angle-minVal) *  ((stopAngle - startAngle) / (maxVal - minVal)) + startAngle;
      let angleInRadians = angleInDegrees * oneDegreeInRadians;

      ctx.rotate(angleInRadians );  
      ctx.moveTo(tickStartPoint, 0 );                   
      ctx.lineTo(tickStartPoint + (tickLength - 10), 0 );
      ctx.stroke();
      
      ctx.rotate(-angleInRadians);  //  this puts the dial back where it was. 
  }
// ******************************************************************
    // draw the pointer
    
    // map the value to a degree
    let pointerAngleInDegrees =  (dialValue-minVal) *  ((stopAngle - startAngle) / (maxVal - minVal)) + startAngle  ;
    let pointerAngleInRadians = pointerAngleInDegrees * oneDegreeInRadians;

    let pointerLength = radius*0.86;
    let pointerWidth = W/100 * 2; 
    
    ctx.beginPath();
    ctx.lineWidth = pointerWidth;
    ctx.lineCap = 'round';  
    ctx.moveTo(0,0);
    ctx.rotate(pointerAngleInRadians);
    ctx.lineTo(pointerLength, 0);
    ctx.stroke();
    ctx.rotate(-pointerAngleInRadians);
  
    // reset the coordinates ready for next time    
    ctx.restore();
  }

  function drawGraph(canvasID, gMin, gMax, drawLines, t,h, tempArray, humdArray)
  {

    // Graph Init - draw the graph but do not draw values.
  
    var c = document.getElementById(canvasID);
    var ctx = c.getContext('2d');
    ctx.clearRect(0, 0, c.width, c.height); 

    var graphWidth  = c.width;
    var graphHeight = c.height; 
      
    var fontSize = '8px Arial';
    var fontAdjust = 3;
    if (graphHeight < 100) { fontSize = '6px Arial'; fontAdjust = 1;}
    
    var numySteps = gMax - gMin;
    if (numySteps > 10) { numySteps = numySteps /10; }
    var numxSteps = tempArray.length;

    var xStep = graphWidth / numxSteps;
    var yStep = graphHeight / numySteps;
  
    ctx.lineWidth = 1;
    ctx.strokeStyle = '#e5e5e5';
    ctx.lineCap = 'butt';
        for (let x = 0; x < c.width; x=x+xStep) 
    { 
       ctx.moveTo(x, 0);    ctx.lineTo(x, c.height);     ctx.stroke();
    }

        for (let y = 0; y <= numySteps; y++) 
    { 
       let yPos = y * yStep;
       ctx.moveTo(0, yPos);    ctx.lineTo(c.width,yPos);    ctx.stroke();
    }
    
    // draw labels    
    ctx.font = fontSize;
    ctx.fillStyle = '#000000';
     
    // no need to draw the first or the last label
    for (let i = 1; i < numySteps; i++)
    {
         let yPos = c.height - i * yStep;
         let tmp = i * 10;
         tmp = tmp + gMin;
         let txt = tmp.toString();
         ctx.fillText(txt, 2, yPos + fontAdjust);        
    }
      
    // draw the  values on the graph  
    if (drawLines)
    {
        // Temperature        
        ctx.beginPath();
        ctx.lineWidth = 1;  
        ctx.strokeStyle = '#ff7777';  
        ctx.fillStyle   = '#ff4444';  
    
        // on the first value we are not coming from an existing point so we just need to move to the coordinates ready to plot value 2.
        let firstValue = true;

        for (let i = 0; i < numxSteps; i++) 
        { 
            if (tempArray[i] != -9999) 
            {
                let tmpVal = tempArray[i] ;
                let yPos = (tmpVal - gMin) * (graphHeight - 0)/( gMax - gMin ) + 0;
                yPos = graphHeight - yPos;
                let xPos = (i*xStep) + xStep;
                
                // draw the line
                if (firstValue)   { ctx.moveTo(xPos, yPos); firstValue = false;  }
                else              { ctx.lineTo(xPos,yPos);  ctx.stroke();  }
            
                // draw the dot
                ctx.beginPath(); ctx.arc(xPos, yPos, 3, 0, 2 * Math.PI, false);  ctx.fill();
            }
        }
      
        // Humidity
        ctx.lineWidth = 1;  
        ctx.strokeStyle = '#7777ff';  
        ctx.fillStyle   = '#4444ff';    
        ctx.beginPath();
    
        // on the first value we are not coming from an existing point so we just need to move to the coordinates ready to plot value 2.
        firstValue = true;
  
        for (let i = 0; i < numxSteps; i++) 
        { 
            if (humdArray[i] != -9999)  
            {
                let tmpVal = humdArray[i] ;
                let yPos = (tmpVal - gMin) * (graphHeight - 0)/( gMax - gMin ) + 0;
                yPos = graphHeight - yPos;
                let xPos = (i*xStep) + xStep;
                
                // draw the line
                if (firstValue)   {  ctx.moveTo(xPos, yPos);  firstValue = false;  }
                else              {  ctx.lineTo(xPos,yPos);   ctx.stroke();  }
      
                // draw the dot
                ctx.beginPath();  ctx.arc(xPos, yPos, 3, 0, 2 * Math.PI, false);  ctx.fill();
            }
        }

    } // if (! initOnly)
  } // function drawGraph
  
  function processReceivedData(evt) 
  {
    var data = evt.data;
    console.log(data);

    var tmp = data.split('|');

    // convert the received string in to numbers
    var h = parseInt(tmp[0]);
    var t = parseFloat(tmp[1]);
    var cpt = parseInt(tmp[3]);

    // arrays to hold the temperature and humidity values.
    var tempArray = [ parseFloat(tmp[4]),parseFloat(tmp[6]),parseFloat(tmp[8]),parseFloat(tmp[10]),parseFloat(tmp[12]),parseFloat(tmp[14]),parseFloat(tmp[16]),parseFloat(tmp[18]),parseFloat(tmp[20]),parseFloat(tmp[22]),parseFloat(tmp[24]),parseFloat(tmp[26]),parseFloat(tmp[28]),parseFloat(tmp[30]),parseFloat(tmp[32]),parseFloat(tmp[34]),parseFloat(tmp[36]),parseFloat(tmp[38]),parseFloat(tmp[40]),parseFloat(tmp[42])];
    var humdArray = [ parseFloat(tmp[5]),parseFloat(tmp[7]),parseFloat(tmp[9]),parseFloat(tmp[11]),parseFloat(tmp[13]),parseFloat(tmp[15]),parseFloat(tmp[17]),parseFloat(tmp[19]),parseFloat(tmp[21]),parseFloat(tmp[23]),parseFloat(tmp[25]),parseFloat(tmp[27]),parseFloat(tmp[29]),parseFloat(tmp[31]),parseFloat(tmp[33]),parseFloat(tmp[35]),parseFloat(tmp[37]),parseFloat(tmp[39]),parseFloat(tmp[41]),parseFloat(tmp[43])];


    updateValues(h,t,b, tempArray, humdArray, cpt);
    
    var b = b + 1;
    if (b > 12){b = 0;}
  }

  function updateTime() 
  {  
     var d = new Date();
     var t = d.toLocaleTimeString();
     var j = d.toLocaleDateString();
     
     document.getElementById('time').innerHTML = t;     
     document.getElementById('date').innerHTML = j;
  }

  // This is executed after the document has finished loading.
  function init() 
  {
    Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
    Socket.onmessage = function(event) { processReceivedData(event); };
    
    console.log('started');
    drawDial('canvasTemp',  '#ffaaaa', 160, 20, 20,  50, 0); 
    drawDial('canvasHumid', '#aaaaff', 160, 20,   0, 100, 0);
    drawGraph('grahp', 20, 100, false, t, h, tempArray, humdArray);
    
    var myVarTime = setInterval(updateTime, 1000); 
  }
  
  // arrays to hold the temperature and humidity values.
  var tempArray = [ -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999 ];
  var humdArray = [ -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999 ];
 
  var t = 20.0;
  var h = 50.0;
  var cpt = 0;
  
  document.addEventListener('DOMContentLoaded', init, false);
   
  // ]]>
  </script>
    
</html> 
)=="==";
