/*
 * File:   VirtIONet.h
 * Author: s0457958
 *
 * Created on 25 September 2014, 14:40
 */

#ifndef VIRTIONET_H
#define	VIRTIONET_H

#include "abi/devices/virtio/VirtIO.h"
#include "abi/devices/generic/net/NetworkInterface.h"

#include <list>
#include <mutex>

namespace archsim
{
	namespace abi
	{
		namespace devices
		{
			namespace virtio
			{
				class VirtIONet : public VirtIO, public generic::net::NetworkInterfaceReceiveCallback
				{
				public:
					VirtIONet(EmulationModel& parent_model, IRQLine& irq, Address base_address, std::string name, generic::net::NetworkInterface &iface, uint64_t mac_address);
					virtual ~VirtIONet();

					void receive_packet(const uint8_t *buffer, uint32_t length) override;

				protected:
					uint8_t *GetConfigArea() const override
					{
						return (uint8_t *)&config;
					}
					uint32_t GetConfigAreaSize() const override
					{
						return sizeof(config);
					}

					void ResetDevice() override;

				private:
					void ProcessEvent(VirtIOQueueEvent* evt) override;

					generic::net::NetworkInterface &_iface;

					std::mutex _receive_buffer_lock;
					std::list<VirtIOQueueEvent*> _receive_buffers;

					struct {
						uint8_t mac[6];
						uint16_t status;
					} config;


					struct virtio_net_hdr {
						uint8_t flags;
						uint8_t gso_type;
						uint16_t hdr_len;
						uint16_t gso_size;
						uint16_t csum_start, csum_offset;
						uint16_t num_buffers;
					} __packed;
				};
			}
		}
	}
}

#endif	/* VIRTIONET_H */

