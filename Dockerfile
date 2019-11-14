FROM linuxmintd/mint19-amd64 
RUN apt update && apt install -y --no-install-recommends \ 
					wget \ 
					p7zip \
					ca-certificates-java \ 
					default-jre \ 
					default-jre-headless \ 
					java-common \
					libel-api-java \ 
					libhsqldb1.8.0-java \ 
					libjsp-api-java \
					libservlet-api-java \
					libservlet3.1-java \
					libwebsocket-api-java \
					openjdk-11-jre:amd64 \
					openjdk-11-jre-headless:amd64 \
					build-essential \
					pkg-config autoconf \
					automake \
					libtool \
					libusb-dev \
					libusb-1.0-0-dev \
					libhidapi-dev \
					libftdi-dev && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash giovanni
USER giovanni
WORKDIR /home/giovanni
RUN mkdir -p /home/giovanni/Projects/
WORKDIR /home/giovanni/Projects
RUN wget -O cbs.7z https://osdn.net/projects/chibios/downloads/71342/ChibiStudio_Linux_Preview2.7z/ && p7zip -d cbs.7z 
CMD /home/giovanni/Projects/ChibiStudio/ChibiStudio-GCC8.3.1


