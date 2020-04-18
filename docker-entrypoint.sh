#!/bin/bash
if [[ -z "${PUBLIC_KEY_PATH}" ]]; then
  echo "PUBLIC_KEY_PATH env variable not provided. Terminating."
  exit 1
else
  cat "$PUBLIC_KEY_PATH" >> /root/.ssh/authorized_keys \
    && /usr/sbin/sshd \
    && tail -f /dev/null
fi