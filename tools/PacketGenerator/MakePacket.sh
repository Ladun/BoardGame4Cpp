#!/bin/bash
python ./PacketGenerator.py --output=ClientPacketHandler\
                            --recv=C_ --send=S_\
                            --path=../protoc/bin/Protocol.proto
python ./PacketGenerator.py --output=ServerPacketHandler\
                            --recv=S_ --send=C_\
                            --path=../protoc/bin/Protocol.proto
                            
cp ./ClientPacketHandler.hpp ../../Server/Server/Packet/ClientPacketHandler.hpp
cp ./ServerPacketHandler.hpp ../../Client/Client/Network/ServerPacketHandler.hpp

cd ../protoc/bin

protoc --cpp_out=./ Protocol.proto

cp ./Protocol.pb.cc ../../../Server/Server/Packet
cp ./Protocol.pb.h ../../../Server/Server/Packet
cp ./Protocol.pb.cc ../../../Client/Client/Network/Packet
cp ./Protocol.pb.h ../../../Client/Client/Network/Packet
