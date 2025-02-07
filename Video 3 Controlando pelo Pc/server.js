const express = require('express');
const axios = require('axios');
const app = express();
const port = 3000;

// Configuração do IP do ESP8266 - atualize com o IP do seu ESP8266
const ESP_IP = 'http://192.168.1.100'; // Substitua pelo IP do seu ESP8266

// Servir arquivos estáticos da pasta public
app.use(express.static('public'));

// Rota para ligar/desligar os relés
app.get('/control/:relay/:action', async (req, res) => {
  const { relay, action } = req.params;
  try {
    await axios.get(`${ESP_IP}/${relay}/${action}`);
    res.json({ success: true });
  } catch (error) {
    res.status(500).json({ error: 'Falha ao controlar o relé' });
  }
});

// Rota para obter status dos relés
app.get('/status', async (req, res) => {
  try {
    const response = await axios.get(`${ESP_IP}/status`);
    res.json(response.data);
  } catch (error) {
    res.status(500).json({ error: 'Falha ao obter status' });
  }
});

app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`);
});