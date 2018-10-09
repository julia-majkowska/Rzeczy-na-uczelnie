FROM ubuntu

ENV ROUTER_DIR /var/www/router

ADD . ${ROUTER_DIR}
WORKDIR ${ROUTER_DIR}

#RUN apt-get update && apt-get install -y \
#     logrotate libmosquitto1 libstdc++6 libc6 libgcc1 \
#     curl \
#     && rm -rf /var/lib/apt/lists/*
#RUN apt-get -qq update && \
#     apt-get -qq -y install \
#         build-essential
#    make -C ${ROUTER_DIR}/src

# CMD ["sh", "-c", "echo .${ROUTER_DIR}/src/router < test1/${MACHINE_NAME}"]

CMD ["sleep", "infinity"]

