#!/bin/bash
echo "Aguardando conexão ADB..."
adb wait-for-device
echo "Dispositivo detectado! Coletando arquivos de /sys/fs/pstore/..."

OUT_DIR="/home/adrianojr59/Vídeos/NX809J_Android16_kernel/scratch"
mkdir -p "$OUT_DIR"

echo "=== Lista de arquivos ===" > "$OUT_DIR/ramoops.log"
adb shell "su -c 'ls -la /sys/fs/pstore/'" >> "$OUT_DIR/ramoops.log" 2>&1

echo -e "\n=== Conteúdo dos logs ===" >> "$OUT_DIR/ramoops.log"
for file in $(adb shell "su -c 'ls /sys/fs/pstore/'" 2>/dev/null | tr -d '\r'); do
    echo "--- Arquivo: $file ---" >> "$OUT_DIR/ramoops.log"
    adb shell "su -c 'cat /sys/fs/pstore/$file'" >> "$OUT_DIR/ramoops.log" 2>&1
done

echo "Concluído! Logs salvos em $OUT_DIR/ramoops.log"
