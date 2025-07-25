#include "embarcatech-estacao-meteorologica.h"

const char HTML_BODY[] =  "<!DOCTYPE html>\n"
    "<html lang=\"pt-br\">\n"
    "<head>\n"
    "<meta charset=\"UTF-8\">\n"
    "<title>Estação Meteorológica</title>\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    "<style>\n"
    "body{font-family:Arial,sans-serif;margin:20px;background:#338e6b;}"
    "h1{color:#333;}"
    ".container{background:#fff;padding:20px;border-radius:8px;max-width:800px;margin:auto;box-shadow:0 2px 10px rgba(0,0,0,0.08);}"
    ".data-panel{display:flex;flex-direction:row;margin-bottom:30px;gap:16px}"
    ".data-box{background:#e2e2e1;padding:16px;border-radius:6px;flex:1;text-align:center;}"
    ".data-box h2{margin-bottom:10px;font-size:1.2em;}"
    ".data-value{font-size:2em;color:#338e6b;}"
    ".charts-col{display:flex;flex-direction:column;gap:20px;margin-bottom:30px;}"
    ".chart-box{background:#e2e2e1;border-radius:6px;padding:10px;}"
    ".cards-panel{display:flex;flex-direction:row;gap:20px;margin-bottom:30px;}"
    ".card{background:#e2e2e1;border-radius:6px;padding:16px;flex:1;box-shadow:0 1px 5px rgba(0,0,0,0.05);}"
    ".card-title{font-weight:bold;margin-bottom:8px;color:#333;}"
    ".card-content{font-size:1.1em;}"
    ".forms-panel{display:flex;gap:20px;flex-wrap:wrap;}"
    "form{background:#e2e2e1;padding:14px;border-radius:6px;margin-bottom:15px;min-width:280px;flex:1;box-shadow:0 1px 5px rgba(0,0,0,0.05);}"
    "form h3{margin-top:0;}"
    "label{display:block;margin-top:8px;margin-bottom:4px;}"
    "input[type=\"number\"]{width:80px;padding:4px;}"
    "input[type=\"submit\"]{margin-top:12px;padding:7px 14px;background:#338e6b;color:#fff;border:none;border-radius:4px;cursor:pointer;}"
    "@media (max-width: 480px) {.data-panel, .cards-panel{flex-direction: column;align-items: stretch;width:100%;}}"
    "\n"
    "</style>\n"
    "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n"
    "</head>\n"
    "<body>\n"
    "<div class=\"container\">\n"
    "<h1>Estação Meteorológica</h1>\n"
    "<div class=\"data-panel\">\n"
    "<div class=\"data-box\">\n"
    "<h2>Status</h2>\n"
    "<span class=\"data-value\" id=\"statusValue\">--</span>\n"
    "</div>\n</div>\n"
    "<div class=\"data-panel\">\n"
    "<div class=\"data-box\">\n"
    "<h2>Temperatura</h2>\n"
    "<span class=\"data-value\" id=\"tempValue\">-- °C</span>\n"
    "</div>\n"
    "<div class=\"data-box\">\n"
    "<h2>Umidade</h2>\n"
    "<span class=\"data-value\" id=\"humValue\">-- %</span>\n"
    "</div>\n"
    "<div class=\"data-box\">\n"
    "<h2>Altitude</h2>\n"
    "<span class=\"data-value\" id=\"altValue\">-- m</span>\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"charts-col\">\n"
    "<div class=\"chart-box\">\n"
    "<canvas id=\"tempChart\" height=\"150\"></canvas>\n"
    "</div>\n"
    "<div class=\"chart-box\">\n"
    "<canvas id=\"humChart\" height=\"150\"></canvas>\n"
    "</div>\n"
    "<div class=\"chart-box\">\n"
    "<canvas id=\"altChart\" height=\"150\"></canvas>\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"cards-panel\">\n"
    "<div class=\"card\">\n"
    "<div class=\"card-title\">Limites de Temperatura</div>\n"
    "<div class=\"card-content\">\n"
    "Mínimo: <span id=\"cardTempMin\">--</span> °C<br>\n"
    "Máximo: <span id=\"cardTempMax\">--</span> °C\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"card\">\n"
    "<div class=\"card-title\">Limites de Umidade</div>\n"
    "<div class=\"card-content\">\n"
    "Mínimo: <span id=\"cardHumMin\">--</span> %<br>\n"
    "Máximo: <span id=\"cardHumMax\">--</span> %\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"card\">\n"
    "<div class=\"card-title\">Offset de Temperatura</div>\n"
    "<div class=\"card-content\">\n"
    "<span id=\"cardTempOffset\">--</span> °C\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"card\">\n"
    "<div class=\"card-title\">Offset de Umidade</div>\n"
    "<div class=\"card-content\">\n"
    "<span id=\"cardHumOffset\">--</span> %\n"
    "</div>\n"
    "</div>\n"
    "</div>\n"
    "<div class=\"forms-panel\">\n"
    "<form id=\"formTempLim\">\n"
    "<h3>Definir Limites de Temperatura</h3>\n"
    "<label for=\"tempMin\">Mínimo (°C):</label>\n"
    "<input type=\"number\" id=\"tempMin\" name=\"tempMin\" value=\"20\">\n"
    "<label for=\"tempMax\">Máximo (°C):</label>\n"
    "<input type=\"number\" id=\"tempMax\" name=\"tempMax\" value=\"30\">\n"
    "<input type=\"submit\" value=\"Salvar\">\n"
    "</form>\n"
    "<form id=\"formHumLim\">\n"
    "<h3>Definir Limites de Umidade</h3>\n"
    "<label for=\"humMin\">Mínimo (%):</label>\n"
    "<input type=\"number\" id=\"humMin\" name=\"humMin\" step=\"0.1\" value=\"40\">\n"
    "<label for=\"humMax\">Máximo (%):</label>\n"
    "<input type=\"number\" id=\"humMax\" name=\"humMax\" step=\"0.1\" value=\"70\">\n"
    "<input type=\"submit\" value=\"Salvar\">\n"
    "</form>\n"
    "<form id=\"formTempOffset\">\n"
    "<h3>Ajustar Offset de Temperatura</h3>\n"
    "<label for=\"tempOffset\">Offset (°C):</label>\n"
    "<input type=\"number\" id=\"tempOffset\" name=\"tempOffset\" step=\"0.1\" value=\"0\">\n"
    "<input type=\"submit\" value=\"Salvar\">\n"
    "</form>\n"
    "<form id=\"formHumOffset\">\n"
    "<h3>Ajustar Offset de Umidade</h3>\n"
    "<label for=\"humOffset\">Offset (%):</label>\n"
    "<input type=\"number\" id=\"humOffset\" name=\"humOffset\" step=\"0.1\" value=\"0\">\n"
    "<input type=\"submit\" value=\"Salvar\">\n"
    "</form>\n"
    "</div>\n"
    "</div>\n"
    "<script>\n"
    "document.addEventListener(\"DOMContentLoaded\", function() {\n"
    "let tempData = [];\n"
    "let humData = [];\n"
    "let altData = [];\n"
    "const tempCtx = document.getElementById('tempChart').getContext('2d');\n"
    "const humCtx = document.getElementById('humChart').getContext('2d');\n"
    "const altCtx = document.getElementById('altChart').getContext('2d');\n"
    "const tempChart = new Chart(tempCtx, {\n"
    "type: 'line',\n"
    "data: {\n"
    "labels: tempData.map(() => \"\"), // No labels\n"
    "datasets: [{\n"
    "label: 'Temperatura',\n"
    "data: tempData,\n"
    "borderColor: '#338e6b',\n"
    "backgroundColor: '#338e6b',\n"
    "pointBackgroundColor: '#338e6b',\n"
    "pointRadius: 2,\n"
    "fill: false\n"
    "}]\n"
    "}\n"
    "});\n"
    "const humChart = new Chart(humCtx, {\n"
    "type: 'line',\n"
    "data: {\n"
    "labels: humData.map(() => \"\"), // No labels\n"
    "datasets: [{\n"
    "label: 'Umidade',\n"
    "data: humData,\n"
    "borderColor: '#338e6b',\n"
    "backgroundColor: '#338e6b',\n"
    "pointBackgroundColor: '#338e6b',\n"
    "pointRadius: 2,\n"
    "fill: false\n"
    "}]\n"
    "}\n"
    "});\n"
    "const altChart = new Chart(altCtx, {\n"
    "type: 'line',\n"
    "data: {\n"
    "labels: altData.map(() => \"\"), // No labels\n"
    "datasets: [{\n"
    "label: 'Altitude',\n"
    "data: altData,\n"
    "borderColor: '#338e6b',\n"
    "backgroundColor: '#338e6b',\n"
    "pointBackgroundColor: '#338e6b',\n"
    "pointRadius: 2,\n"
    "fill: false\n"
    "}]\n"
    "}\n"
    "});\n"
    "function updateData() {\n"
    "fetch('/station/state')\n"
    ".then(res => res.json())\n"
    ".then(state => {\n"
    "document.getElementById('tempValue').innerText = state.temp + \" °C\";\n"
    "document.getElementById('humValue').innerText = state.hum + \" %\";\n"
    "document.getElementById('altValue').innerText = state.alt + \" m\";\n"
    "document.getElementById('cardTempMin').innerText = state.temp_min;\n"
    "document.getElementById('cardTempMax').innerText = state.temp_max;\n"
    "document.getElementById('cardHumMin').innerText = state.hum_min;\n"
    "document.getElementById('cardHumMax').innerText = state.hum_max;\n"
    "document.getElementById('cardTempOffset').innerText = state.temp_offset;\n"
    "document.getElementById('cardHumOffset').innerText = state.hum_offset;\n"
    "document.getElementById('statusValue').innerText = (state.status === 0x00 ? 'OK' : 'Erro');\n"
    "if (tempData.length >= 10) {\n"
    "tempData.shift();\n"
    "}\n"
    "tempData.push(state.temp);\n"
    "tempChart.data.labels = tempData.map(() => \"\");\n"
    "tempChart.data.datasets[0].data = tempData;\n"
    "tempChart.update();\n"
    "if (humData.length >= 10) {\n"
    "humData.shift();\n"
    "}\n"
    "humData.push(state.hum);\n"
    "humChart.data.labels = humData.map(() => \"\");\n"
    "humChart.data.datasets[0].data = humData;\n"
    "humChart.update();\n"
    "if (altData.length >= 10) {\n"
    "altData.shift();\n"
    "}\n"
    "altData.push(state.alt);\n"
    "altChart.data.labels = altData.map(() => \"\");\n"
    "altChart.data.datasets[0].data = altData;\n"
    "altChart.update();\n"
    "});\n"
    "}\n"
    "\n"
    "setInterval(updateData, 3000);\n"
    "window.onload = updateData;\n"
    "\n"
    "document.getElementById(\"formTempLim\").onsubmit = async function(e) {\n"
    "e.preventDefault();\n"
    "const min = document.getElementById(\"tempMin\").value;\n"
    "const max = document.getElementById(\"tempMax\").value;\n"
    "await fetch('/limits/temp', {\n"
    "method:\"POST\",\n"
    "headers:{\"Content-Type\":\"application/x-www-form-urlencoded\"},\n"
    "body:`temp_min=${min}&temp_max=${max}`\n"
    "});\n"
    "updateData();\n"
    "};\n"
    "document.getElementById(\"formHumLim\").onsubmit = async function(e) {\n"
    "e.preventDefault();\n"
    "const min = document.getElementById(\"humMin\").value;\n"
    "const max = document.getElementById(\"humMax\").value;\n"
    "await fetch('/limits/hum', {\n"
    "method:\"POST\",\n"
    "headers:{\"Content-Type\":\"application/x-www-form-urlencoded\"},\n"
    "body:`hum_min=${min}&hum_max=${max}`\n"
    "});\n"
    "updateData();\n"
    "};\n"
    "document.getElementById(\"formTempOffset\").onsubmit = async function(e) {\n"
    "e.preventDefault();\n"
    "const offset = document.getElementById(\"tempOffset\").value;\n"
    "await fetch(\"/offset/temp\", {\n"
    "method:\"POST\",\n"
    "headers:{\"Content-Type\":\"application/x-www-form-urlencoded\"},\n"
    "body:`temp_offset=${offset}`\n"
    "});\n"
    "updateData();\n"
    "};\n"
    "document.getElementById(\"formHumOffset\").onsubmit = async function(e) {\n"
    "e.preventDefault();\n"
    "const offset = document.getElementById(\"humOffset\").value;\n"
    "await fetch(\"/offset/hum\", {\n"
    "method:\"POST\",\n"
    "headers:{\"Content-Type\":\"application/x-www-form-urlencoded\"},\n"
    "body:`hum_offset=${offset}`\n"
    "});\n"
    "updateData();\n"
    "};\n"
    "});\n"
    "</script>\n"
    "</body>\n"
    "</html>\n";


static err_t http_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
    struct http_state *hs = (struct http_state *)arg;
    hs->sent += len;
    if (hs->sent >= hs->len)
    {
        tcp_close(tpcb);
        free(hs);
    }
    return ERR_OK;
}

static err_t http_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (!p)
    {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char *req = (char *)p->payload;
    struct http_state *hs = malloc(sizeof(struct http_state));
    if (!hs)
    {
        pbuf_free(p);
        tcp_close(tpcb);
        return ERR_MEM;
    }

    hs->sent = 0;


    if (strstr(req, "GET /station/state"))
    {
        char json_payload[256];
        int json_len = 0;

        if(xSemaphoreTake(xStationDataMutex, portMAX_DELAY) == pdTRUE) {
            json_len = snprintf(json_payload, sizeof(json_payload),
            "{\"temp\":%.1f,\"hum\":%.1f,\"alt\":%.0lf, \"temp_offset\":%.1lf, \"hum_offset\":%.1lf,\"status\":%d,",
            station_data_global.aht20_data.temperature,
            station_data_global.aht20_data.humidity,
            station_data_global.altitude,
            station_data_global.temp_offset,
            station_data_global.hum_offset,
            station_data_global.status);
            xSemaphoreGive(xStationDataMutex);
        }

        if(xSemaphoreTake(xStationLimitsMutex, portMAX_DELAY) == pdTRUE) {
            json_len += snprintf(json_payload+json_len, sizeof(json_payload)-json_len,
            "\"temp_min\":%.1f,\"temp_max\":%.1f,\"hum_min\":%.1lf,\"hum_max\":%.1f}\r\n",
            station_limits_global.min_temperature,
            station_limits_global.max_temperature,
            station_limits_global.min_humidity,
            station_limits_global.max_humidity);

            xSemaphoreGive(xStationLimitsMutex);
        }

        
        hs->len = snprintf(hs->response, sizeof(hs->response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            json_len, json_payload);
    }
    else if (strstr(req, "POST /limits/temp"))
    {
        UpdateData_t new_data;
        new_data.type = LIMITS_TEMP;

        char *body = strstr(req, "\r\n\r\n");
        if (body)
        {
            sscanf(body, "\r\n\r\ntemp_min=%f&temp_max=%f", &new_data.min, &new_data.max);
            xQueueSend(xQueueUpdateData, &new_data, portMAX_DELAY);
        }

        hs->len = snprintf(hs->response, sizeof(hs->response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nOK");
    
    }else if (strstr(req, "POST /limits/hum")) {
        UpdateData_t new_data;
        new_data.type = LIMITS_HUM;

        char *body = strstr(req, "\r\n\r\n");
        if (body)
        {
            sscanf(body, "\r\n\r\nhum_min=%f&hum_max=%f", &new_data.min, &new_data.max);
            xQueueSend(xQueueUpdateData, &new_data, portMAX_DELAY);
        }
        hs->len = snprintf(hs->response, sizeof(hs->response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nOK");

    }else if (strstr(req, "POST /offset/temp")) {
        UpdateData_t new_data;
        new_data.type = OFFSET_TEMP;
        new_data.max = 0; // Inicializa o segundo valor como 0
        
        char *body = strstr(req, "\r\n\r\n");
        if (body)
        {
            sscanf(body, "\r\n\r\ntemp_offset=%f", &new_data.min);
            xQueueSend(xQueueUpdateData, &new_data, portMAX_DELAY);
        }

        hs->len = snprintf(hs->response, sizeof(hs->response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nOK");
    
    }else if (strstr(req, "POST /offset/hum")) {
        UpdateData_t new_data;
        new_data.type = OFFSET_HUM;
        new_data.max = 0; // Inicializa o segundo valor como 0

        char *body = strstr(req, "\r\n\r\n");
        int offset = 0;
        if (body)
        {
            sscanf(body, "\r\n\r\nhum_offset=%f", &new_data.min);
            xQueueSend(xQueueUpdateData, &new_data, portMAX_DELAY);
        }

        hs->len = snprintf(hs->response, sizeof(hs->response),
            "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nOK");
    }else
    {
        hs->len = snprintf(hs->response, sizeof(hs->response),
                           "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: %d\r\n"
                           "Connection: close\r\n"
                           "\r\n"
                           "%s",
                           (int)strlen(HTML_BODY), HTML_BODY);
    }

    tcp_arg(tpcb, hs);
    tcp_sent(tpcb, http_sent);

    tcp_write(tpcb, hs->response, hs->len, TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    pbuf_free(p);
    return ERR_OK;
}

static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{

    tcp_recv(newpcb, http_recv);
    return ERR_OK;
}

static void start_http_server(void)
{
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb)
    {
        printf("Erro ao criar PCB TCP\n");
        return;
    }
    if (tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK)
    {
        printf("Erro ao ligar o servidor na porta 80\n");
        return;
    }
    pcb = tcp_listen(pcb);
    tcp_accept(pcb, connection_callback);
    printf("Servidor HTTP rodando na porta 80...\n");
}

// Função para sinalizar uma tarefa a partir de uma ISR
void signal_task_from_isr(SemaphoreHandle_t xSemaphore)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;                // Variável para verificar se uma tarefa de maior prioridade foi despertada
    xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken); // Libera o semáforo e verifica se uma tarefa de maior prioridade foi despertada
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);                 // Se uma tarefa de maior prioridade foi despertada, realiza um yield para que ela possa ser executada imediatamente
}

// Função de tratamento de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t now = us_to_ms(get_absolute_time());

    if (gpio == BUTTONA_GPIO && (now - last_time_button_A > DEBOUNCE_TIME))
    {
        last_time_button_A = now;
        signal_task_from_isr(xDisplayViewSemaphore);
    }
}

/**
 * @brief Tarefa responsável por implementar o servidor TCP.
 *
 * Esta tarefa executa a lógica do servidor TCP, aceitando conexões de clientes,
 * recebendo e enviando dados conforme necessário. 
 * 
 */
void vTaskTCPServer(){
    
    while (true) {
        cyw43_arch_poll();
        vTaskDelay(pdMS_TO_TICKS(100)); // Mantém o loop ativo para processar eventos Wi-Fi
    }

    // Finaliza a arquitetura CYW43
    cyw43_arch_deinit();
    vTaskDelete(NULL); // Deleta a tarefa atual

}

void vTaskSensorPolling(void *pvParameters) {
    int32_t raw_temp_bmp;
    int32_t raw_pressure;
    float pressure;
    

    Station_data_t station_data; // Estrutura para armazenar os dados da estação meteorológica
    Station_limits_t station_limits; // Estrutura para armazenar os limites de temperatura e umidade

    struct bmp280_calib_param *params = (struct bmp280_calib_param *)pvParameters;

    /* ---------------------- Configuracao de parametros ------------------------ */
    station_limits.min_temperature = MIN_TEMPERATURE;
    station_limits.max_temperature = MAX_TEMPERATURE;
    station_limits.min_humidity = MIN_HUMIDITY;
    station_limits.max_humidity = MAX_HUMIDITY;
    
    station_data.hum_offset = 0;
    station_data.temp_offset = 0;

    
    while (true) {
        /* ---------------- Leitura de sensores ----------------*/
        // Leitura do BMP280
        bmp280_read_raw(I2C_PORT, &raw_temp_bmp, &raw_pressure);
        station_data.temperature_bmp = bmp280_convert_temp(raw_temp_bmp, params) / 100.0;
        pressure = bmp280_convert_pressure(raw_pressure, raw_temp_bmp, params) / 1000.0;
        
        station_data.altitude = calculate_altitude(pressure * 1000.0);


        // Leitura do AHT20
        if (!aht20_read(I2C_PORT, &station_data.aht20_data)) {
            printf("Erro na leitura do AHT20!\n\n\n");
        }

        // Adicionando offset a temperatura e umidade
        station_data.temperature_bmp += station_data.temp_offset;
        station_data.aht20_data.temperature += station_data.temp_offset;
        station_data.aht20_data.humidity += station_data.hum_offset;


        if (xSemaphoreTake(xStationLimitsMutex, portMAX_DELAY) == pdTRUE) {
            station_limits = station_limits_global; // Atualiza os limites da estação
            xSemaphoreGive(xStationLimitsMutex);
        }

        /* ---------------------- Atualizando estado do sistema -------------------*/
        if (station_data.aht20_data.temperature < station_limits.min_temperature || station_data.aht20_data.temperature > station_limits.max_temperature) {
            station_data.status |= 0x0F;
        } else {
            station_data.status &= ~0x0F;
        }

        if (station_data.aht20_data.humidity < station_limits.min_humidity || station_data.aht20_data.humidity > station_limits.max_humidity) {
            station_data.status |= 0xF0;
        } else {
            station_data.status &= ~0xF0;
        }
              
        if (xSemaphoreTake(xStationDataMutex, portMAX_DELAY) == pdTRUE) {
            station_data_global.temperature_bmp = station_data.temperature_bmp; // Atualiza os dados da estação meteorológica
            station_data_global.altitude = station_data.altitude;
            station_data_global.aht20_data = station_data.aht20_data;
            station_data.temp_offset = station_data_global.temp_offset;
            station_data.hum_offset = station_data_global.hum_offset;
            station_data_global.status = station_data.status;
            xSemaphoreGive(xStationDataMutex);
        }

        xQueueSend(xQueueStationStatus1, &station_data.status, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(200)); // Polling a cada 200 milissegundos
    }

    vTaskDelete(NULL); // Deleta a tarefa atual
}

void vTaskDisplay(void *pvParameters) {
    ssd1306_t *ssd = (ssd1306_t *)pvParameters;

    Station_data_t station_data;
    Station_limits_t station_limits;

    uint8_t *ip = (uint8_t *)&(cyw43_state.netif[0].ip_addr.addr);
    char ip_str[24];
    snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    bool data_view = true;

    while (true) {
        // Selecionando tipo de visualizacao
        if (xSemaphoreTake(xDisplayViewSemaphore, 0) == pdTRUE)
        {
            data_view = !data_view; // Alterna entre as views
        }

        if (xSemaphoreTake(xStationDataMutex, portMAX_DELAY) == pdTRUE){
                station_data = station_data_global; // Obtém os dados da estação meteorológica
                xSemaphoreGive(xStationDataMutex);
        }

        /* ----------------- Display data view ----------------- */
        if (data_view) {

            char temp_bmp_str[7];
            char altitude_str[6];
            char temp_aht_str[7];
            char humidity_aht_str[7];
            snprintf(temp_bmp_str, sizeof(temp_bmp_str), "%.1fC", station_data.temperature_bmp);
            snprintf(altitude_str, sizeof(altitude_str), "%.0lfm", station_data.altitude);
            snprintf(temp_aht_str, sizeof(temp_aht_str), "%.1fC", station_data.aht20_data.temperature);
            snprintf(humidity_aht_str, sizeof(humidity_aht_str), "%.1f%%", station_data.aht20_data.humidity);

            ssd1306_fill(ssd, false); // Limpa o display
            ssd1306_rect(ssd, 3, 3, 122, 60, true, false);       // Desenha um retângulo
            ssd1306_line(ssd, 3, 25, 123, 25, true);            // Desenha uma linha
            ssd1306_line(ssd, 3, 37, 123, 37, true);            // Desenha uma linha
            ssd1306_draw_string(ssd, ip_str, 13, 6);  // Desenha uma string
            ssd1306_draw_string(ssd, cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) == CYW43_LINK_UP ? "   Connected  " : "  Disconnected ", 5, 16);   // Desenha uma string
            ssd1306_draw_string(ssd, " BMP     AHT", 10, 28); // Desenha uma string
            ssd1306_line(ssd, 63, 25, 63, 60, true);            // Desenha uma linha vertical
            ssd1306_draw_string(ssd, temp_bmp_str, 14, 41);             // Desenha uma string
            ssd1306_draw_string(ssd, altitude_str, 14, 52);             // Desenha uma string
            ssd1306_draw_string(ssd, temp_aht_str, 73, 41);             // Desenha uma string
            ssd1306_draw_string(ssd, humidity_aht_str, 73, 52);            // Desenha uma string
            ssd1306_send_data(ssd);                            // Atualiza o display

            ssd1306_send_data(ssd); // Envia os dados para o display
 

        }else{
            char temp_min_str[7];
            char temp_max_str[7];
            char hum_min_str[7];
            char hum_max_str[7];
            char temp_offset_str[7];
            char hum_offset_str[7];

            if(xSemaphoreTake(xStationLimitsMutex, portMAX_DELAY) == pdTRUE)
            {
                station_limits = station_limits_global; // Obtém os limites da estação meteorológica
                xSemaphoreGive(xStationLimitsMutex);
            }

            snprintf(temp_min_str, sizeof(temp_min_str), "%.1fC", station_limits.min_temperature);
            snprintf(temp_max_str, sizeof(temp_max_str), "%.1fC", station_limits.max_temperature);
            snprintf(hum_min_str, sizeof(hum_min_str), "%.1f%%", station_limits.min_humidity);
            snprintf(hum_max_str, sizeof(hum_max_str), "%.1f%%", station_limits.max_humidity);
            snprintf(temp_offset_str, sizeof(temp_offset_str), "%.1fC", station_data.temp_offset);
            snprintf(hum_offset_str, sizeof(hum_offset_str), "%.1f%%", station_data.hum_offset);

            ssd1306_fill(ssd, false); // Limpa o display
            ssd1306_rect(ssd, 3, 3, 122, 60, true, false);       // Desenha um retângulo
            ssd1306_draw_string(ssd, " TEMP  UMIDADE", 10, 5); // Desenha uma string

            ssd1306_draw_string(ssd, temp_min_str, 14, 15);             // Desenha uma string
            ssd1306_draw_string(ssd, temp_max_str, 14, 25);             // Desenha uma string
            ssd1306_draw_string(ssd, hum_min_str, 73, 15);              // Desenha uma string
            ssd1306_draw_string(ssd, hum_max_str, 73, 25);              // Desenha uma string
            ssd1306_draw_string(ssd, "    OFFSET    ", 10, 40);         // Desenha uma string
            ssd1306_draw_string(ssd, temp_offset_str, 14, 50);          // Desenha uma string
            ssd1306_draw_string(ssd, hum_offset_str, 73, 50);           // Desenha uma string
            ssd1306_vline(ssd, 63, 3, 35, true);                        // Desenha uma linha vertical
            ssd1306_hline(ssd, 3, 125, 36, true);                       // Desenha uma linha horizontal
            ssd1306_send_data(ssd);                                     // Atualiza o display
        }

        vTaskDelay(pdMS_TO_TICKS(250)); // Atualiza a cada 250 milissegundos
    }

    vTaskDelete(NULL); // Deleta a tarefa atual
}

void vTaskLedMtx(void *pvParameters) {
    uint8_t station_status = 0;

    Led_mtx_data_t *mtx_data = (Led_mtx_data_t *) pvParameters; // Recebe a estrutura Led_mtx_data_t como parâmetro
    uint led_mask = (1u << RED_LED_GPIO) | (1u << GREEN_LED_GPIO) | (1u << BLUE_LED_GPIO);

    char frames[4][5][5] = {
        {{'g', 'g', 'g', 'g', 'g'},
        {'g', 'o', 'o', 'o', 'g'},
        {'g', 'o', 'g', 'o', 'g'},
        {'g', 'o', 'o', 'o', 'g'},
        {'g', 'g', 'g', 'g', 'g'}},
        
        {{'y', 'o', 'o', 'o', 'y'},
        {'o', 'y', 'o', 'y', 'o'},
        {'o', 'o', 'y', 'o', 'o'},
        {'o', 'y', 'o', 'y', 'o'},
        {'y', 'o', 'o', 'o', 'y'}},

        {{'p', 'o', 'o', 'o', 'p'},
        {'o', 'p', 'o', 'p', 'o'},
        {'o', 'o', 'p', 'o', 'o'},
        {'o', 'p', 'o', 'p', 'o'},
        {'p', 'o', 'o', 'o', 'p'}},
        
        {{'r', 'o', 'o', 'o', 'r'},
        {'o', 'r', 'o', 'r', 'o'},
        {'o', 'o', 'r', 'o', 'o'},
        {'o', 'r', 'o', 'r', 'o'},
        {'r', 'o', 'o', 'o', 'r'}},

    };

    matrix_turn_all(mtx_data->pio, mtx_data->state_machine, 0.0, 0.0, 0.0); // Desliga todos os LEDs inicialmente
    
    while(true){
        if(xQueueReceive(xQueueStationStatus1, &station_status, portMAX_DELAY) == pdTRUE){
            switch(station_status){
                case 0x00: // Estado normal
                    matrix_display_frame(mtx_data->pio, mtx_data->state_machine, frames[0]);
                    gpio_put_masked(led_mask, (1u << GREEN_LED_GPIO)); // LED verde para estado normal
                    break;
                case 0x0F: // Estado de temperatura
                    matrix_display_frame(mtx_data->pio, mtx_data->state_machine, frames[1]);
                    gpio_put_masked(led_mask, (1u << GREEN_LED_GPIO) | (1u << RED_LED_GPIO)); 
                    break;
                case 0xF0: // Estado de umidade
                    matrix_display_frame(mtx_data->pio, mtx_data->state_machine, frames[2]);
                    gpio_put_masked(led_mask, (1u << BLUE_LED_GPIO) | (1u << RED_LED_GPIO)); 
                    break;
                case 0xFF:
                    matrix_display_frame(mtx_data->pio, mtx_data->state_machine, frames[3]);
                    gpio_put_masked(led_mask,(1u << RED_LED_GPIO)); 
                    break;
                default:
                    break;
            }
        }   
    }
}


void vTaskUpdateParam(void *pvParameters) {
    UpdateData_t update_data;

    while (true) {
        if (xQueueReceive(xQueueUpdateData, &update_data, portMAX_DELAY) == pdTRUE) {
            printf("Atualizando dados: Tipo=%d, Valores=[%f, %f]\n", update_data.type, update_data.min, update_data.max);
            switch (update_data.type) {
                case LIMITS_TEMP:
                    if (xSemaphoreTake(xStationLimitsMutex, portMAX_DELAY) == pdTRUE) {
                        station_limits_global.min_temperature = update_data.min;
                        station_limits_global.max_temperature = update_data.max;
                        xSemaphoreGive(xStationLimitsMutex);
                    }
                    break;
                case LIMITS_HUM:
                    if (xSemaphoreTake(xStationLimitsMutex, portMAX_DELAY) == pdTRUE) {
                        station_limits_global.min_humidity = update_data.min;
                        station_limits_global.max_humidity = update_data.max;
                        xSemaphoreGive(xStationLimitsMutex);
                    }
                    break;
                case OFFSET_TEMP:
                    if (xSemaphoreTake(xStationDataMutex, portMAX_DELAY) == pdTRUE) {
                        station_data_global.temp_offset = update_data.min;
                        xSemaphoreGive(xStationDataMutex);
                    }
                    break;
                case OFFSET_HUM:
                    if (xSemaphoreTake(xStationDataMutex, portMAX_DELAY) == pdTRUE) {
                        station_data_global.hum_offset = update_data.min;
                        xSemaphoreGive(xStationDataMutex);
                    }
                    break;
            }
        }
    }

    vTaskDelete(NULL); // Deleta a tarefa atual
}


int main(){
    /* ------------- Configura o clock do sistema para 125 kHz ------------------ */
    set_sys_clock_khz(125000, false);

    /* ------------------- Inicializacao de perifericos ------------------------- */
    stdio_init_all();

    // Configurando botoes
    gpio_init(BUTTONA_GPIO); // Inicializa o GPIO do botão A
    gpio_set_dir(BUTTONA_GPIO, GPIO_IN); // Configura o GPIO do botão
    gpio_pull_up(BUTTONA_GPIO); // Ativa pull-up no GPIO do botão A
    gpio_set_irq_enabled_with_callback(BUTTONA_GPIO, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção para o botão A

    // Configurando led
    uint led_mask = (1u << RED_LED_GPIO) | (1u << GREEN_LED_GPIO) | (1u << BLUE_LED_GPIO);
    gpio_init_mask(led_mask); // Inicializa os GPIOs dos LEDs
    gpio_set_dir_masked(led_mask, led_mask); // Configura os GPIOs dos LEDs
    gpio_put_masked(led_mask, 0); // Desliga todos os LEDs

    // Configurando matriz de leds
    Led_mtx_data_t mtx_data;

    mtx_data.pio = pio0; // PIO 0 para a matriz de LEDs
    mtx_data.offset = pio_add_program(mtx_data.pio, &pio_matrix_program);
    mtx_data.state_machine = pio_claim_unused_sm(mtx_data.pio, true);
    pio_matrix_program_init(mtx_data.pio, mtx_data.state_machine, mtx_data.offset, GPIO_LED_MTX);

    // Configurando o I2C
    i2c_setup(); 

    // Configurando o display SSD1306
    ssd1306_t ssd;
    ssd1306_config_gpio(&ssd); // Configura o GPIO para o display SSD

    // Configurando o sensor AHT20
    aht20_reset(I2C_PORT);
    aht20_init(I2C_PORT);

    // Configurando o sensor BMP280
    struct bmp280_calib_param params;
    bmp280_init(I2C_PORT);
    bmp280_get_calib_params(I2C_PORT, &params);

    /* ------------------------ Inicializacao de rede ---------------------------*/

    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, "Iniciando sistema. Por favor aguarde...", 5, 5);
    ssd1306_send_data(&ssd);
    
    if (cyw43_arch_init())
    {
        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "WiFi => FALHA", 0, 0);
        ssd1306_send_data(&ssd);
        return 1;
    }

    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "WiFi => ERRO", 0, 0);
        ssd1306_send_data(&ssd);
        return 1;
    }


    /* ---------------------- Configuracao de parametros ------------------------ */
    station_limits_global.min_temperature = MIN_TEMPERATURE;
    station_limits_global.max_temperature = MAX_TEMPERATURE;
    station_limits_global.min_humidity = MIN_HUMIDITY;
    station_limits_global.max_humidity = MAX_HUMIDITY;

    station_data_global.hum_offset = 0;
    station_data_global.temp_offset = 0;

    

    // Aguarda 2 segundos para estabilizacao de perifericos
    sleep_ms(2000);


    /* --------------------  Criacao de tasks e mutexes -------------------- */

    start_http_server(); // Inicia o servidor HTTP

    xStationDataMutex = xSemaphoreCreateMutex(); 
    xStationLimitsMutex = xSemaphoreCreateMutex(); // Mutex para acesso aos limites da estação
    xDisplayViewSemaphore = xSemaphoreCreateBinary(); // Semáforo para controle de acesso ao display

    xQueueStationStatus1 = xQueueCreate(10, sizeof(uint8_t)); // Cria a fila para status da estação 1
    xQueueUpdateData = xQueueCreate(10, sizeof(UpdateData_t)); // Cria a fila para atualização de dados


    xTaskCreate(vTaskTCPServer, "Task TCP Server", configMINIMAL_STACK_SIZE + 128, NULL, 1, NULL);
    xTaskCreate(vTaskSensorPolling, "Task Sensor Polling", configMINIMAL_STACK_SIZE + 128, &params, 1, NULL);
    xTaskCreate(vTaskDisplay, "Task Display", configMINIMAL_STACK_SIZE + 128, &ssd, 1, NULL);
    xTaskCreate(vTaskLedMtx, "Task LED Matrix", configMINIMAL_STACK_SIZE + 128, &mtx_data, 1, NULL);
    xTaskCreate(vTaskUpdateParam, "Task Update Param", configMINIMAL_STACK_SIZE + 128, NULL, 1, NULL);

    vTaskStartScheduler(); // Inicia o escalonador de tarefas

    panic_unsupported(); // Se o escalonador falhar, entra em pânico
}


void ssd1306_config_gpio(ssd1306_t *ssd) {
    ssd1306_init(ssd, DISPLAY_WIDTH, DISPLAY_HEIGHT, false, DISPLAY_ADDRESS, I2C_PORT_SSD1306);
    ssd1306_config(ssd);

    ssd1306_fill(ssd, false); // Limpa o display
    ssd1306_send_data(ssd); // Envia os dados para o display
}

void i2c_setup(){

    // Inicializa o I2C
    i2c_init(I2C_PORT_SSD1306, 400 * 1000); // Inicializa o I2C a 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);

    // Configura os pinos I2C
    gpio_set_function(I2C_SDA_SSD1306, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_SSD1306, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_SDA_SSD1306); // Ativa pull-up no pino SDA
    gpio_pull_up(I2C_SCL_SSD1306); // Ativa pull-up no pino SCL
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

// Função para calcular a altitude a partir da pressão atmosférica
double calculate_altitude(double pressure)
{
    return 44330.0 * (1.0 - pow(pressure / SEA_LEVEL_PRESSURE, 0.1903));
}

