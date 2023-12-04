/* yeneid/yeneid--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION heapy" to load this file. \quit

CREATE FUNCTION heapy_tableam_handler(internal)
RETURNS table_am_handler
AS 'MODULE_PATHNAME'
LANGUAGE C;

-- Access method
CREATE ACCESS METHOD heapy TYPE TABLE HANDLER heapy_tableam_handler;
COMMENT ON ACCESS METHOD heapy IS 'table AM for Yezzey/Yeneid metadata';


CREATE OR REPLACE FUNCTION heapy_define_relation_offload_policy_internal(reloid OID) RETURNS void
AS 'MODULE_PATHNAME'
VOLATILE
EXECUTE ON COORDINATOR
LANGUAGE C STRICT;


CREATE OR REPLACE FUNCTION heapy_define_relation_offload_policy_internal_seg(reloid OID) RETURNS void
AS 'MODULE_PATHNAME'
VOLATILE
EXECUTE ON ALL SEGMENTS
LANGUAGE C STRICT;

