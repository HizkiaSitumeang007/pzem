<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
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
        .table-container {
            display: inline-block;
            margin: 20px;
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
        .toggle-button {
            width: 60px;
            height: 30px;
            background-color: #555;
            border-radius: 15px;
            position: relative;
            cursor: pointer;
            transition: background 0.3s ease;
            display: inline-block;
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
    </style>
</head>
<body>
    <div class="container">
        <h1>PZEM-004T Data Monitoring</h1>
        <div class="table-container">
            <table>
                <tr><th colspan="2">PZEM 1</th></tr>
                <tr><th>Voltage</th><td id="voltage1">- V</td></tr>
                <tr><th>Current</th><td id="current1">- A</td></tr>
                <tr><th>Power</th><td id="power1">- W</td></tr>
                <tr><th>Energy</th><td id="energy1">- kWh</td></tr>
                <tr><th>Frequency</th><td id="frequency1">- Hz</td></tr>
                <tr><th>Power Factor</th><td id="pf1">-</td></tr>
            </table>
            <div class="toggle-button" id="toggle1" onclick="toggleSwitch(1)"></div>
        </div>
        <div class="table-container">
            <table>
                <tr><th colspan="2">PZEM 2</th></tr>
                <tr><th>Voltage</th><td id="voltage2">- V</td></tr>
                <tr><th>Current</th><td id="current2">- A</td></tr>
                <tr><th>Power</th><td id="power2">- W</td></tr>
                <tr><th>Energy</th><td id="energy2">- kWh</td></tr>
                <tr><th>Frequency</th><td id="frequency2">- Hz</td></tr>
                <tr><th>Power Factor</th><td id="pf2">-</td></tr>
            </table>
            <div class="toggle-button" id="toggle2" onclick="toggleSwitch(2)"></div>
        </div>
    </div>
    <script>
        function toggleSwitch(id) {
            const toggle = document.getElementById(`toggle${id}`);
            const isOn = toggle.classList.toggle("toggle-on");
            localStorage.setItem(`toggle${id}`, isOn);
            
            // Kirim request ke ESP32
            fetch(`/led${id}/toggle`)
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error("Error:", error));
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

        document.addEventListener("DOMContentLoaded", restoreToggles);
    </script>
</body>
</html>
