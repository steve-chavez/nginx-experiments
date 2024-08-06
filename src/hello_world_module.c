#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r) {
    ngx_buf_t    *b;

    ngx_str_t response = ngx_string("Hello, World!");

    r->headers_out = (ngx_http_headers_out_t) {
      .status = NGX_HTTP_OK,
      .content_length_n = response.len,
      .content_type = (ngx_str_t) ngx_string("text/plain"),
    };

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_chain_t out = {
      .buf = b,
      .next = NULL,
    };

    b->pos = response.data;
    b->last = response.data + response.len;
    b->memory = 1;    /* this buffer is in memory */
    b->last_buf = 1;  /* this is the last buffer in the response */

    ngx_http_send_header(r);
    return ngx_http_output_filter(r, &out);
}

static char *ngx_set_command(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
}

ngx_module_t ngx_http_hello_world_module = {
    NGX_MODULE_V1,
    &(ngx_http_module_t){0},
   (ngx_command_t[]){
      {
        .name = ngx_string("hello_world"),
        .type = NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
        .set = ngx_set_command,
      },
      ngx_null_command
    },
    NGX_HTTP_MODULE,                  /* module type */
    NULL,                             /* init master */
    NULL,                             /* init module */
    NULL,                             /* init process */
    NULL,                             /* init thread */
    NULL,                             /* exit thread */
    NULL,                             /* exit process */
    NULL,                             /* exit master */
    NGX_MODULE_V1_PADDING
};

