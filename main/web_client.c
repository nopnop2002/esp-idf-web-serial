/*
	Example using WEB Socket.
	This example code is in the Public Domain (or CC0 licensed, at your option.)
	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "client_task";

#include "websocket_server.h"

extern MessageBufferHandle_t xMessageBufferToClient;
extern MessageBufferHandle_t xMessageBufferToUart;

void client_task(void* pvParameters) {
	ESP_LOGI(TAG, "Start");
	char messageBuffer[512];
	while(1) {
		size_t readBytes = xMessageBufferReceive(xMessageBufferToClient, messageBuffer, sizeof(messageBuffer), portMAX_DELAY );
		ESP_LOGD(TAG, "readBytes=%d", readBytes);
		cJSON *root = cJSON_Parse(messageBuffer);
		if (cJSON_GetObjectItem(root, "id")) {
			char *id = cJSON_GetObjectItem(root,"id")->valuestring;
			ESP_LOGD(TAG, "id=%s",id);

			// Do something when the browser started
			if ( strcmp (id, "init") == 0) {
			} // end of init

			// Do something when the send button pressed.
			if ( strcmp (id, "send-request") == 0) {
				xMessageBufferSend(xMessageBufferToUart, messageBuffer, readBytes, portMAX_DELAY);
			} // end of send-request

			if ( strcmp (id, "recv-request") == 0) {
				char *payload = cJSON_GetObjectItem(root,"payload")->valuestring;
				time_t now;
				struct tm *tm_now;
				now = time(NULL);
				now = now + (CONFIG_LOCAL_TIMEZONE*60*60);
				tm_now = localtime(&now);
				ESP_LOGD(TAG, "DATE %04d/%02d/%02d", tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday);
				ESP_LOGD(TAG, "TIME %02d:%02d:%02d", tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);

				char out[256];
				char DEL = 0x04;
				//int outlen = sprintf(out,"RECEIVE%c%s%c%s", DEL, "datetime", DEL, "payload");
				int outlen = sprintf(out,"RECEIVE%c%02d:%02d:%02d%c%s", DEL, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec, DEL, payload);
				ESP_LOGD(TAG,"outlen=%d out-[%s]", outlen, out);
				ws_server_send_text_all(out, outlen);
			} // end of recv-request

		}
		cJSON_Delete(root);
	}
	vTaskDelete(NULL);
}
