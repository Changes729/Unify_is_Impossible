# Punch Clock

## 3rdparty

## 编译

json 库需要在 json库的 `CMakeLists.txt` 中修改 `target_compile_features(${NLOHMANN_JSON_TARGET_NAME} INTERFACE cxx_std_17)`，不然编译不过

MIFARE_CLASSIC_BASIC_DEFAULT_SEARCH_DELAY_MS 需要修改为 `0`，不然它会很卡。

## 音频

当前系统仅支持 pcm_s16le 格式的音频，转码参考: `ffmpeg -i in.wav -ac 2 -ar 44100 -c:a pcm_s16le out.wav`

视频是 `yuv420` 格式的

## 交互操作

### Mac（PC）

- `Q`: 退出程序
- `0`: 模拟收到了RFID （ID：12345678）
- `1`: 模拟保存配置文件
- `-`: 音量-
- `=`: 音量+

### Linux（ARM）

ARM Linux下可以用 RFID 进行配置，配置文件是 [JSON](https://www.json.org/json-en.html) 格式。

- 音量：
    - `{"VOLUME": "1"}` ：音量+
    - `{"VOLUME": "0"}` ：音量-（非正值，字符串）
- 设备ID：`{"ID": "1234"}`
- 服务器：`{"URL": "http://192.168.1.2"}`（末尾不带：）
- 资源路径：`{"PATH": "./resource"}` 默认是 `resource` 目录

往往，设备ID和服务器会在一起配置：
```json
{
  "ID": "1234",
  "URL": "http://192.168.1.2"
}
```