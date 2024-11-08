// Configurações do Firebase
const firebaseConfig = {
  apiKey: "AIzaSyDL8vGcnqRaJlro48xDdG9sIU7-6VY4p_Y",
  authDomain: "monitoramento-de-abelhas.firebaseapp.com",
  databaseURL: "https://monitoramento-de-abelhas-default-rtdb.firebaseio.com",
  projectId: "monitoramento-de-abelhas",
  storageBucket: "monitoramento-de-abelhas.appspot.com",
  messagingSenderId: "946858093055",
  appId: "1:946858093055:web:73ef584c624858dab65fca",
  measurementId: "G-KCWK9K2ZXQ"
};

// Inicializa Firebase
firebase.initializeApp(firebaseConfig);
firebase.analytics();

const database = firebase.database();

// Referências para os dados no Firebase
const tempRef = database.ref('/sensores/Temperatura');
const beeCountRef = database.ref('/sensores/Contador');

// Elementos HTML
const tempElement = document.getElementById('tempValue');
const beeCountElement = document.getElementById('beeCount');

// Atualizar temperatura e contagem em tempo real
tempRef.on('value', (snapshot) => {
  const temp = snapshot.val();
  tempElement.textContent = temp;
  updateTempChart(temp);
});

beeCountRef.on('value', (snapshot) => {
  const count = snapshot.val();
  beeCountElement.textContent = count;
  updateBeeChart(count);
});

// Gráficos
let tempData = [];
let beeData = [];
let tempLabels = []; // Labels independentes para o gráfico de temperatura
let beeLabels = [];  // Labels independentes para o gráfico de contagem de abelhas

const tempCtx = document.getElementById('tempChart').getContext('2d');
const tempChart = new Chart(tempCtx, {
  type: 'line',
  data: {
    labels: tempLabels, // Usa labels específicos para temperatura
    datasets: [{
      label: 'Temperatura (°C)',
      data: tempData,
      borderColor: 'rgba(255, 99, 132, 1)',
      borderWidth: 2
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Horário'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Temperatura (°C)'
        },
        beginAtZero: true
      }
    }
  }
});

const beeCtx = document.getElementById('beeChart').getContext('2d');
const beeChart = new Chart(beeCtx, {
  type: 'line',
  data: {
    labels: beeLabels, // Usa labels específicos para contagem de abelhas
    datasets: [{
      label: 'Movimentação de Abelhas',
      data: beeData,
      borderColor: 'rgba(54, 162, 235, 1)',
      borderWidth: 2
    }]
  },
  options: {
    scales: {
      x: {
        title: {
          display: true,
          text: 'Horário'
        }
      },
      y: {
        title: {
          display: true,
          text: 'Contagem'
        },
        beginAtZero: true
      }
    }
  }
});

// Funções para atualizar os gráficos
function updateTempChart(temperature) {
  const currentTime = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }); // Exibe apenas hora e minuto
  tempLabels.push(currentTime); // Atualiza labels do gráfico de temperatura
  tempData.push(Math.floor(temperature));  // Arredonda para baixo
  tempChart.update(); 
}

function updateBeeChart(count) {
  const currentTime = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }); // Exibe apenas hora e minuto
  beeLabels.push(currentTime); // Atualiza labels do gráfico de contagem de abelhas
  beeData.push(count);
  beeChart.update();
}
