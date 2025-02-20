<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="5">
    <title>PZEM Monitor</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #121212;
            color: #ffffff;
            text-align: center;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 900px;
            margin: 50px auto;
            background: #1e1e1e;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(255, 255, 255, 0.1);
        }
        h1 {
            color: #ffffff;
        }
        .tables {
            display: flex;
            justify-content: space-around;
            align-items: center;
            flex-wrap: wrap;
            gap: 20px;
        }
        table {
            width: 300px;
            border-collapse: collapse;
            background-color: #252525;
            border-radius: 10px;
            overflow: hidden;
        }
        th, td {
            border: 1px solid #333;
            padding: 10px;
            text-align: center;
            color: #ffffff;
        }
        th {
            background-color: #007BFF;
            color: white;
        }
        .control {
            display: flex;
            align-items: center;
            gap: 10px;
        }
        .toggle-button {
            width: 60px;
            height: 30px;
            background-color: #555;
            border-radius: 15px;
            position: relative;
            cursor: pointer;
            transition: background 0.3s ease;
        }
        .toggle-button::before {
            content: "";
            position: absolute;
            width: 26px;
            height: 26px;
            background-color: white;
            border-radius: 50%;
            top: 2px;
            left: 2px;
            transition: transform 0.3s ease;
        }
        .toggle-on {
            background-color: #28a745 !important;
        }
        .toggle-on::before {
            transform: translateX(30px);
        }
        .circle {
            width: 20px;
            height: 20px;
            border-radius: 50%;
            display: inline-block;
            background-color: red;
        }
        .circle.green {
            background-color: green;
        }
        /* New styles for the reload button */
        .reload-button {
            background-color: #007BFF;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 25px;
            font-size: 16px;
            cursor: pointer;
            transition: background-color 0.3s ease, transform 0.3s ease;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.2);
        }
        .reload-button:hover {
            background-color: #0056b3;
            transform: scale(1.05);
        }
        .reload-button:active {
            transform: scale(0.95);
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>PZEM-004T Data Monitoring</h1>
        <button class="reload-button" onclick="reloadPage()">⟳ Reload</button>
        <div class="tables">
            <div class="table-container">
                <table>
                    <tr><th colspan="2">PZEM 1</th></tr>
                    <tr><th>Parameter</th><th>Value</th></tr>
                    <tr><td>Voltage</td><td id="voltage1">- V</td></tr>
                    <tr><td>Current</td><td id="current1">- A</td></tr>
                    <tr><td>Power</td><td id="power1">- W</td></tr>
                    <tr><td>Energy</td><td id="energy1">- kWh</td></tr>
                    <tr><td>Frequency</td><td id="frequency1">- Hz</td></tr>
                    <tr><td>Power Factor</td><td id="pf1">-</td></tr>
                </table>
                <div class="control">
                    <div class="toggle-button" id="toggle1" onclick="toggleSwitch(1)"></div>
                    <div id="circle1" class="circle"></div>
                </div>
            </div>
            <div class="table-container">
                <table>
                    <tr><th colspan="2">PZEM 2</th></tr>
                    <tr><th>Parameter</th><th>Value</th></tr>
                    <tr><td>Voltage</td><td id="voltage2">- V</td></tr>
                    <tr><td>Current</td><td id="current2">- A</td></tr>
                    <tr><td>Power</td><td id="power2">- W</td></tr>
                    <tr><td>Energy</td><td id="energy2">- kWh</td></tr>
                    <tr><td>Frequency</td><td id="frequency2">- Hz</td></tr>
                    <tr><td>Power Factor</td><td id="pf2">-</td></tr>
                </table>
                <div class="control">
                    <div class="toggle-button" id="toggle2" onclick="toggleSwitch(2)"></div>
                    <div id="circle2" class="circle"></div>
                </div>
            </div>
        </div>
    </div>
    <script>
        function toggleSwitch(id) {
            const toggle = document.getElementById(`toggle${id}`);
            const isOn = toggle.classList.toggle("toggle-on");
            localStorage.setItem(`toggle${id}`, isOn);
        }

        function updateCircleStatus() {
            const current1 = parseFloat(document.getElementById("current1").textContent) || 0;
            const current2 = parseFloat(document.getElementById("current2").textContent) || 0;
            document.getElementById("circle1").classList.toggle("green", current1 > 0);
            document.getElementById("circle2").classList.toggle("green", current2 > 0);
        }

        function restoreToggles() {
            for (let i = 1; i <= 2; i++) {
                const toggle = document.getElementById(`toggle${i}`);
                const isOn = localStorage.getItem(`toggle${i}`) === "true";
                if (isOn) {
                    toggle.classList.add("toggle-on");
                }
            }
        }

        function reloadPage() {
            fetch('/refresh-ip').then(() => location.reload());
        }

        document.addEventListener("DOMContentLoaded", () => {
            restoreToggles();
            updateCircleStatus();
        });
    </script>
</body>
</html>
