/*
 * gtp.h
 *
 * GPRS Tunneling Protocol (TS 29.281)
 *
 */

#ifndef DNET_GTP_H
#define DNET_GTP_H

#include <stdint.h>

struct gtpv1_hdr {
	uint8_t gtp_flags;
	uint8_t gtp_type;
	uint16_t gtp_len;
	uint32_t gtp_teid;
	uint16_t gtp_seqno;
	uint8_t gtp_npdu;
	uint8_t gtp_next;
} __attribute__((__packed__));

struct gtpv2_hdr {
	uint8_t gtp_flags;
	uint8_t gtp_type;
	uint16_t gtp_len;
	union {
		struct {
			uint32_t gtp_teid;
			uint32_t gtp_seqno:24;
			uint32_t gtp_spare:8;
		} t;
		struct {
			uint32_t gtp_seqno:24;
			uint32_t gtp_spare:8;
		} nt;
	} e;
} __attribute__((__packed__));

#define GTPV1_HDR_LEN sizeof(struct gtpv1_hdr)
#define GTPV2_HDR_LEN sizeof(struct gtpv2_hdr)

#define GTP_MIN_HDR_LEN 8
#define GTP_MAX_HDR_LEN 12

#define GTP_PORT_CONTROL  2123
#define GTP_PORT_USER     2152

#define GTP_FLAGS_PROTO_V0      (0 << 5)
#define GTP_FLAGS_PROTO_V1      (1 << 5)
#define GTP_FLAGS_PROTO_V2      (2 << 5)

#define GTP_FLAGS_TYPE_GTPP     (0 << 4)
#define GTP_FLAGS_TYPE_GTP      (1 << 4)

#define GTP_FLAGS_TEID_PRESENT  (1 << 3)
#define GTP_FLAGS_NEXT_PRESENT  (1 << 2)
#define GTP_FLAGS_SEQNO_PRESENT (1 << 1)
#define GTP_FLAGS_NPDU_PRESENT  (1 << 0)

/* Common messages */
#define GTP_TYPE_ECHO_REQUEST                                    0x01
#define GTP_TYPE_ECHO_RESPONSE                                   0x02
#define GTP_TYPE_VERSION_NOT_SUPPORTED_INDICATION                0x03

/* GTPv1 */
#define GTP_TYPE_NODE_ALIVE_REQUEST                              0x04
#define GTP_TYPE_NODE_ALIVE_RESPONSE                             0x05
#define GTP_TYPE_REDIRECT_REQUEST                                0x06
#define GTP_TYPE_REDIRECT_RESPONSE                               0x07
#define GTP_TYPE_CREATE_PDP_REQUEST                              0x10
#define GTP_TYPE_CREATE_PDP_RESPONSE                             0x11
#define GTP_TYPE_UPDATE_PDP_REQUEST                              0x12
#define GTP_TYPE_UPDATE_PDP_RESPONSE                             0x13
#define GTP_TYPE_DELETE_PDP_REQUEST                              0x14
#define GTP_TYPE_DELETE_PDP_RESPONSE                             0x15
#define GTP_TYPE_CREATE_AA_PDP_REQUEST                           0x16
#define GTP_TYPE_CREATE_AA_PDP_RESPONSE                          0x17
#define GTP_TYPE_DELETE_AA_PDP_REQUEST                           0x18
#define GTP_TYPE_DELETE_AA_PDP_RESPONSE                          0x19
#define GTP_TYPE_ERROR_INDICATION                                0x1a
#define GTP_TYPE_PDU_NOTIFY_REQUEST                              0x1b
#define GTP_TYPE_PDU_NOTIFY_RESPONSE                             0x1c
#define GTP_TYPE_PDU_NOTIFY_REJECT_REQUEST                       0x1d
#define GTP_TYPE_PDU_NOTIFY_REJECT_RESPONSE                      0x1e
#define GTP_TYPE_EXTENSION_HEADERS                               0x1f

#define GTP_TYPE_SEND_ROUTE_INFO_REQUEST                         0x20
#define GTP_TYPE_SEND_ROUTE_INFO_RESPONSE                        0x21
#define GTP_TYPE_FAILURE_REPORT_REQUEST                          0x22
#define GTP_TYPE_FAILURE_REPORT_RESPONSE                         0x23
#define GTP_TYPE_MS_PRESENT_REQUEST                              0x24
#define GTP_TYPE_MS_PRESENT_RESPONSE                             0x25
#define GTPV1_TYPE_IDENTIFICATION_REQUEST                          0x30
#define GTPV1_TYPE_IDENTIFICATION_RESPONSE                         0x31
#define GTPV1_TYPE_SGSN_CONTEXT_REQUEST                            0x32
#define GTPV1_TYPE_SGSN_CONTEXT_RESPONSE                           0x33
#define GTPV1_TYPE_SGSN_CONTEXT_ACKNOWLEDGEMENT                    0x34
#define GTPV1_TYPE_FORWARD_RELOCATION_REQUEST                      0x35
#define GTPV1_TYPE_FORWARD_RELOCATION_RESPONSE                     0x36
#define GTPV1_TYPE_FORWARD_RELOCATION_COMPLETE                     0x37
#define GTPV1_TYPE_RELOCATION_CANCEL_REQUEST                       0x38
#define GTPV1_TYPE_RELOCATION_CANCEL_RESPONSE                      0x39
#define GTPV1_TYPE_FORWARD_SRNS_CONTEXT                            0x3A
#define GTPV1_TYPE_FORWARD_RELOCATION_ACKNOWLEDGEMENT              0x3B
#define GTPV1_TYPE_FORWARD_SRNS_CONTEXT_ACKNOWLEDGEMENT            0x3C

/* GTPv2 */
/* SGSN/MME to PGW (S4/S11, S5/S8) */
#define GTP_TYPE_CREATE_SESSION_REQUEST                          0x20
#define GTP_TYPE_CREATE_SESSION_RESPONSE                         0x21
#define GTP_TYPE_MODIFY_BEARER_REQUEST                           0x22
#define GTP_TYPE_MODIFY_BEARER_RESPONSE                          0x23
#define GTP_TYPE_DELETE_SESSION_REQUEST                          0x24
#define GTP_TYPE_DELETE_SESSION_RESPONSE                         0x25

/* SGSN to PGW (S4, S5/S8) */
#define GTP_TYPE_CHANGE_NOTIFICATION_REQUEST                     0x26
#define GTP_TYPE_CHANGE_NOTIFICATION_RESPONSE                    0x27

/* Commands without responses */
#define GTP_TYPE_MODIFY_BEARER_COMMAND                           0x40
#define GTP_TYPE_MODIFY_BEARER_FAILURE                           0x41
#define GTP_TYPE_DELETE_BEARER_COMMAND                           0x42
#define GTP_TYPE_DELETE_BEARER_FAILURE                           0x43
#define GTP_TYPE_BEARER_RESOURCE_COMMAND                         0x44
#define GTP_TYPE_BEARER_RESOURCE_FAILURE                         0x45
#define GTP_TYPE_DOWNLINK_DATA_NOTIFICATION_FAILURE              0x46
#define GTP_TYPE_TRACE_SESSION_ACTIVATION                        0x47
#define GTP_TYPE_STOP_PAGING                                     0x48

/* PGW to SGSN/MME (S5/S8, S4/S11) */
#define GTP_TYPE_CREATE_BEARER_REQUEST                           0x5f
#define GTP_TYPE_CREATE_BEARER_RESPONSE                          0x60
#define GTP_TYPE_UPDATE_BEARER_REQUEST                           0x61
#define GTP_TYPE_UPDATE_BEARER_RESPONSE                          0x62
#define GTP_TYPE_DELETE_BEARER_REQUEST                           0x63
#define GTP_TYPE_DELETE_BEARER_RESPONSE                          0x64

/* PGW to MME, MME to PGW, SGW to PGW, SGW to MME (S5/S8, S11) */
#define GTP_TYPE_DELETE_PDN_CONNECTION_SET_REQUEST               0x65
#define GTP_TYPE_DELETE_PDN_CONNECTION_SET_RESPONSE              0x66

/* MME to MME, SGSN to MME, MME to SGSN, SGSN to SGSN (S3/10/S16) */
#define GTP_TYPE_IDENTIFICATION_REQUEST                          0x80
#define GTP_TYPE_IDENTIFICATION_RESPONSE                         0x81
#define GTP_TYPE_CONTEXT_REQUEST                                 0x82
#define GTP_TYPE_CONTEXT_RESPONSE                                0x83
#define GTP_TYPE_CONTEXT_ACKNOWLEDGE                             0x84
#define GTP_TYPE_FORWARD_RELOCATION_REQUEST                      0x85
#define GTP_TYPE_FORWARD_RELOCATION_RESPONSE                     0x86
#define GTP_TYPE_FORWARD_RELOCATION_COMPLETE_NOTIFICATION        0x87
#define GTP_TYPE_FORWARD_RELOCATION_COMPLETE_ACKNOWLEDGE         0x88
#define GTP_TYPE_FOWARD_ACCESS_CONTEXT_NOTIFICATION              0x89
#define GTP_TYPE_FORWARD_ACCESS_CONTEXT_ACKNOWLEDGE              0x8a
#define GTP_TYPE_RELOCATION_CANCEL_REQUEST                       0x8b
#define GTP_TYPE_RELOCATION_CANCEL_RESPONSE                      0x8c
#define GTP_TYPE_CONFIGURATION_TRANSFER_TUNNEL                   0x8d

/* SGSN to MME, MME to SGSN (S3) */
#define GTP_TYPE_DETACH_NOTIFICATION                             0x95
#define GTP_TYPE_DETACH_ACKNOWLEDGE                              0x96
#define GTP_TYPE_CS_PAGING_INDICATION                            0x97
#define GTP_TYPE_RAN_INFORMATION_RELAY                           0x98
#define GTP_TYPE_ALERT_MME_NOTIFICATION                          0x99
#define GTP_TYPE_ALERT_MME_ACKNOWLEDGE                           0x9a
#define GTP_TYPE_UE_ACTIVITY_NOTIFICATION                        0x9b
#define GTP_TYPE_UE_ACTIVITY_ACKNOWLEDGE                         0x9c

/* MME to SGW (S11) */
#define GTP_TYPE_CREATE_FORWARDING_TUNNEL_REQUEST                0xa0
#define GTP_TYPE_CREATE_FORWARDING_TUNNEL_RESPONSE               0xa1
#define GTP_TYPE_SUSPEND_NOTIFICATION                            0xa2
#define GTP_TYPE_SUSPEND_ACKNOWLEDGE                             0xa3
#define GTP_TYPE_RESUME_NOTIFICATION                             0xa4
#define GTP_TYPE_RESUME_ACKNOWLEDGE                              0xa5
#define GTP_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST  0xa6
#define GTP_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE 0xa7
#define GTP_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_REQUEST  0xa8
#define GTP_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_RESPONSE 0xa9
#define GTP_TYPE_RELEASE_ACCESS_BEARERS_REQUEST                  0xaa
#define GTP_TYPE_RELEASE_ACCESS_BEARERS_RESPONSE                 0xab

/* SGW to SGSN/MME (S4/S11) */
#define GTP_TYPE_DOWNLINK_DATA_NOTIFICATION                      0xb0
#define GTP_TYPE_DOWNLINK_DATA_NOTIFICATION_ACKNOWLEDGEMENT      0xb1

/* SGW to SGSN (S4) */
#define GTP_TYPE_UPDATE_BEARER_COMPLETE                          0xb2

#define GTP_TYPE_UPDATE_PDN_CONNECTION_SET_REQUEST               0xc8
#define GTP_TYPE_UPDATE_PDN_CONNECTION_SET_RESPONSE              0xc9

/* MBMS GW to MME/SGSN (Sm/Sn) */
#define GTP_TYPE_MBMS_SESSION_START_REQUEST                      0xe7
#define GTP_TYPE_MBMS_SESSION_START_RESPONSE                     0xe8
#define GTP_TYPE_MBMS_SESSION_UPDATE_REQUEST                     0xe9
#define GTP_TYPE_MBMS_SESSION_UPDATE_RESPONSE                    0xea
#define GTP_TYPE_MBMS_SESSION_STOP_REQUEST                       0xeb
#define GTP_TYPE_MBMS_SESSION_STOP_RESPONSE                      0xec

#define GTP_TYPE_END_MARKER                                      0xfe

/* GTP-U */
#define GTP_TYPE_T_PDU                                           0xff

#define GTP_IE_CAUSE                     0x01
#define GTP_IE_IMSI                      0x02
#define GTP_IE_RAI                       0x03
#define GTP_IE_TLLI                      0x04
#define GTP_IE_P_TMSI                    0x05
#define GTP_IE_QOS_PROFILE0              0x06
#define GTP_IE_REORDERING_REQUIRED       0x08
#define GTP_IE_AUTH_TRIPLET              0x09
#define GTP_IE_MAP_CAUSE                 0x0b
#define GTP_IE_P_TMSI_S                  0x0c
#define GTP_IE_MS_VALIDATED              0x0d
#define GTP_IE_RECOVERY                  0x0e
#define GTP_IE_SELECTION_MODE            0x0f
#define GTP_IE_TEID_DATAI                0x10
#define GTP_IE_TEID_CONTROL              0x11
#define GTP_IE_TEID_DATAII               0x12
#define GTP_IE_TEARDOWN                  0x13
#define GTP_IE_NSAPI                     0x14
#define GTP_IE_RANAP_CAUSE               0x15
#define GTP_IE_RAB_CONTEXT               0x16
#define GTP_IE_RP_SMS                    0x17
#define GTP_IE_RP                        0x18
#define GTP_IE_PFI                       0x19
#define GTP_IE_CHARGING                  0x1a
#define GTP_IE_TRACE_REF                 0x1b
#define GTP_IE_TRACE_TYPE                0x1c
#define GTP_IE_MS_NOT_REACH              0x1d
#define GTP_IE_CHARGING_ID               0x7f
#define GTP_IE_END_USER_ADDRESS          0x80
#define GTP_IE_ACCESS_POINT_NAME         0x83
#define GTP_IE_PROTOCOL_OPTIONS          0x84
#define GTP_IE_GSN_ADDRESS               0x85
#define GTP_IE_MSISDN                    0x86
#define GTP_IE_QOS                       0x87

#define GTP2_IE_IMSI                     0x01
#define GTP2_IE_CAUSE                    0x02
#define GTP2_IE_RECOVERY                 0x03
#define GTP2_IE_APN                      0x47
#define GTP2_IE_AMBR                     0x48
#define GTP2_IE_EBI                      0x49
#define GTP2_IE_MEI                      0x4b
#define GTP2_IE_MSISDN                   0x4c
#define GTP2_IE_INDICATION               0x4d
#define GTP2_IE_PAA                      0x4f
#define GTP2_IE_BEARER_QOS               0x50
#define GTP2_IE_FLOW_QOS                 0x51
#define GTP2_IE_RAT_TYPE                 0x52
#define GTP2_IE_SERVING_NETWORK          0x53
#define GTP2_IE_BEARER_TFT               0x54
#define GTP2_IE_TAD                      0x55
#define GTP2_IE_ULI                      0x56
#define GTP2_IE_F_TEID                   0x57
#define GTP2_IE_BEARER_CONTEXT           0x5d
#define GTP2_IE_CHARGING_ID              0x5e
#define GTP2_IE_CHARGING                 0x5f
#define GTP2_IE_PDN_TYPE                 0x63
#define GTP2_IE_PROCEDURE_TRANSACTION_ID 0x64
#define GTP2_IE_APN_RESTRICTION          0x7f
#define GTP2_IE_SELECTION_MODE           0x80
#define GTP2_IE_CHANGE_REPORTING_ACTION  0x83

static inline void *gtpv1_pack_hdr(void *buf, uint8_t flags, uint8_t type,
	uint16_t len, uint32_t teid, uint16_t seqno)
{
	struct gtpv1_hdr *hdr = (struct gtpv1_hdr *)buf;
	hdr->gtp_flags = GTP_FLAGS_PROTO_V1 | GTP_FLAGS_TYPE_GTP | flags;
	hdr->gtp_type = type;
	hdr->gtp_len = len + 4;
	hdr->gtp_teid = teid;
	hdr->gtp_seqno = seqno;
	hdr->gtp_npdu = 0;
	hdr->gtp_next = 0;

	return ((char *)buf + 12);
}

static inline void *gtpv2_pack_hdr(void *buf, uint8_t flags, uint8_t type,
	uint16_t len, uint32_t teid, uint32_t seqno)
{
	struct gtpv2_hdr *hdr = (struct gtpv2_hdr *)buf;
	hdr->gtp_flags = GTP_FLAGS_PROTO_V2 | flags;
	hdr->gtp_type = type;
	if (flags & GTP_FLAGS_TEID_PRESENT) {
		hdr->gtp_len = len + 8;
		hdr->e.t.gtp_teid = teid;
		hdr->e.t.gtp_seqno = seqno;
		hdr->e.t.gtp_spare = 0;
		return ((char *)buf + 12);
	} else {
		hdr->gtp_len = len + 4;
		hdr->e.nt.gtp_seqno = seqno;
		hdr->e.nt.gtp_spare = 0;
		return ((char *)buf + 8);
	}
}

#endif
