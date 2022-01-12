const express = require('express');
const axios = require('axios');

const app = express();
app.use(express.json());
app.use(express.static('public'));

const port = 3000;

// What stuff should the arduino show on the 16x2 display

// XXXXXXXXXXXXXXXX
// Hi This is Rohan
// TEMP BTC $40000       

// Openweathermap API - https://api.openweathermap.org/data/2.5/weather?q=London&appid=e35b6160a1b2a3c55241402c5687fa17
// BTC Price API - https://blockchain.info/ticker

let message = "Hi This is Rohan";
let pin8 = "0"; // Dummy LED Pin By Default is Low
let pin9 = "0"; // 
let pin10 = "0"; // 
let pin11 = "0"; //
let pin12 = "0"; // Buzzer 
let temp = "-1"; // Temperature
let BTCPrice = "-1"; // BTC Price

function updateBTCPrice() {
    axios.get('https://blockchain.info/ticker')
    .then(response => {
        if(response.status == 200 && response.data && response.data["USD"]) {
            console.log(response.data["USD"]["last"]);
            BTCPrice = String(response.data["USD"]["last"]);
        }
    })
    .catch(error => {
        console.log(error);
    });
}

function updateTemp() {
    axios.get('https://api.openweathermap.org/data/2.5/weather?q=Kundapura&appid=e35b6160a1b2a3c55241402c5687fa17')
    .then(response => {
        if(response && response["data"]) response = response["data"];
        if(response["main"] && response["main"]["temp"]) temp = String(Math.round(response["main"]["temp"] - 273));
    })
    .catch(error => {
        console.log(error);
    });
}

app.post('/pin8', (req, res) => {
    if(req.body && (req.body.val == 0 || req.body.val == 1)) pin8 = String(req.body.val);
    res.json({
        "val": pin8
    });
});

app.post('/pin9', (req, res) => {
    if(req.body && (req.body.val == 0 || req.body.val == 1)) pin9 = String(req.body.val);
    res.json({
        "val": pin9
    });
});

app.post('/pin10', (req, res) => {
    if(req.body && (req.body.val == 0 || req.body.val == 1)) pin10 = String(req.body.val);
    res.json({
        "val": pin10
    });
});

app.post('/pin11', (req, res) => {
    if(req.body && (req.body.val == 0 || req.body.val == 1)) pin11 = String(req.body.val);
    res.json({
        "val": pin11
    });
});

app.post('/pin12', (req, res) => {
    if(req.body && (req.body.val == 0 || req.body.val == 1)) pin12 = String(req.body.val);
    res.json({
        "val": pin12
    });
});

app.post('/message', (req, res) => {
    console.log(req.body)
    if(req.body && req.body.message) message = String(req.body.message);
    res.json({
        "message": message
    });
});

app.get('/data', (req, res) => {
    try {
        updateBTCPrice();
        updateTemp();
        res.json({
          "BTCPrice": BTCPrice,
          "temp": temp,
          "message": message,
          "pin8": pin8,
          "pin9": pin9,
          "pin10": pin10,
          "pin11": pin11,
          "pin12": pin12,
      });
    } catch(e) {
        console.log(e);
        res.sendStatus(500);
    }
});



app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
});