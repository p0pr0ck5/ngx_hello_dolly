/*
 * ngx_http_hello_dolly.c
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_hello_dolly(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

/* commands made available in the location config */
static ngx_command_t ngx_http_hello_dolly_commands[] = {
	{
		ngx_string("hello_dolly"),			// the directive
		NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,	// lives in a location block, and doesn't take any args
		ngx_http_hello_dolly,				// function callback
		0,									// setup
		0,									// offset
		NULL,								//post-processing
	},

	ngx_null_command
};

/* hello dolly contents */
static char *ngx_hello_dolly_strings[] = {
	"Hello, Dolly\n",
	"It's so nice to have you back where you belong\n",
	"You're lookin' swell, Dolly\n",
	"I can tell, Dolly\n",
	"I can tell, Dolly\n",
	"You're still glowin', you're still crowin'\n",
	"You're still goin' strong\n",
	"We feel the room swayin'\n",
	"While the band's playin'\n",
	"One of your old favourite songs from way back when\n",
	"So, take her wrap, fellas\n",
	"Find her an empty lap, fellas\n",
	"Dolly'll never go away again\n",
	"Hello, Dolly\n",
	"Well, hello, Dolly\n",
	"It's so nice to have you back where you belong\n",
	"You're lookin' swell, Dolly\n",
	"I can tell, Dolly\n",
	"You're still glowin', you're still crowin'\n",
	"You're still goin' strong\n",
	"We feel the room swayin'\n",
	"While the band's playin'\n",
	"One of your old favourite songs from way back when\n",
	"Golly, gee, fellas\n",
	"Find her a vacant knee, fellas\n",
	"Dolly'll never go away\n",
	"Dolly'll never go away\n",
	"Dolly'll never go away again\n",
};

#define NGX_HELLO_DOLLY_STRINGS_NELTS 28

/* we don't need to define any config handlers */
static ngx_http_module_t ngx_http_hello_dolly_module_ctx = {
	NULL,
	NULL,

	NULL,
	NULL,

	NULL,
	NULL,

	NULL,
	NULL
};

/* expose the module to nginx */
ngx_module_t ngx_http_hello_dolly_module = {
	NGX_MODULE_V1,
	&ngx_http_hello_dolly_module_ctx,	// module context
	ngx_http_hello_dolly_commands,		// module commands
	NGX_HTTP_MODULE,					// module type
	NULL,								// more handlers
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING				// lol no idea what the hell this is
};

/* this is where the magic happens */
static ngx_int_t ngx_http_hello_dolly_handler(ngx_http_request_t *r) {
	ngx_int_t rc;
	ngx_buf_t *b;
	ngx_chain_t out;

	// get a random item from the array. yes i know this is a bad way to do it.
	//srand(time(NULL));
	char *hello_dolly_str = ngx_hello_dolly_strings[rand() % NGX_HELLO_DOLLY_STRINGS_NELTS];

	// respond to GET and HEAD requests only
	if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
		return NGX_HTTP_NOT_ALLOWED;
	}

	// discard the request body
	rc = ngx_http_discard_request_body(r);
	if (rc != NGX_OK) {
		return rc;
	}

	// set the Content-Type, Content-Length, and Status headers
	r->headers_out.content_type_len = sizeof("text/plain") - 1;
	r->headers_out.content_type.len = sizeof("text/plain") - 1;
	r->headers_out.content_type.data = (u_char *) "text/plain";
	r->headers_out.content_length_n = strlen(hello_dolly_str);
	r->headers_out.status = NGX_HTTP_OK;
	
	// if this is a HEAD request, just send the header
	if (r->method == NGX_HTTP_HEAD) {
		return ngx_http_send_header(r);
	}

	// allocate a buffer for the response body
	b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
	if (b == NULL) {
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}

	// attach our buffer to the buffer chain
	out.buf = b;
	out.next = NULL;

	// adjust the buffer pointers
	b->pos = (u_char *)hello_dolly_str;
	b->last = (u_char *)hello_dolly_str + strlen(hello_dolly_str);
	b->memory = 1;		// this buffer is in memory
	b->last_buf = 1;	// this is the last buffer in the buffer chain

	rc = ngx_http_send_header(r);

	if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
		return rc;
	}

	return ngx_http_output_filter(r, &out);
}

static char *ngx_http_hello_dolly(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
	ngx_http_core_loc_conf_t *clcf;

	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	clcf->handler = ngx_http_hello_dolly_handler;

	return NGX_CONF_OK;
}
