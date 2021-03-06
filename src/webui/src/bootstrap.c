#include <kore.h>
#include <http.h>
#include <assets.h>
#include <template.h>

int bootstrap_css(struct http_request *req) {
	char		*date;
	time_t		tstamp;

	tstamp = 0;
	if (http_request_header(req, "if-modified-since", &date)) {
		tstamp = kore_date_to_time(date);
		kore_debug("header was present with %ld", tstamp);
	}

	if (tstamp != 0 && tstamp <= asset_mtime_bootstrap_min_css) {
		http_response(req, 304, NULL, 0);
	} else {
		date = kore_time_to_date(asset_mtime_bootstrap_min_css);
		if (date != NULL)
			http_response_header(req, "last-modified", date);

        http_response_header(req, "content-type", "text/css");
        http_response(req,200,asset_bootstrap_min_css,asset_len_bootstrap_min_css);
    }
    return(KORE_RESULT_OK);
}

int logo(struct http_request *req) {
	http_response_header(req, "content-type", "image/png");
	http_response(req, 200, asset_dowse_logo_png, asset_len_dowse_logo_png);
    return(KORE_RESULT_OK);
}

int welcome(struct http_request *req) {
    template_t tmpl;
	attrlist_t attributes;
    struct kore_buf *buf;

    // allocate output buffer
    buf = kore_buf_alloc(1024*1000);

    // load template
    template_load
        (asset_welcome_html, asset_len_welcome_html, &tmpl);
    attributes = attrinit();

    char *hostname = getenv("hostname");
    if(!hostname) hostname = "dowse";
    char *domain = getenv("domain");
    if(!domain) domain = "dowse.it";

    // TODO: reflect configuration
    attrset(attributes, "hostname", hostname);
    attrset(attributes, "domain",   domain);


    // TODO: space to set stuff in the welcome page here

    template_apply(&tmpl,attributes,buf);

	http_response_header(req, "content-type", "text/html");
	http_response(req, 200, buf->data, buf->offset);

    template_free(&tmpl);
    attrfree(attributes);

    kore_buf_free(buf);

    return(KORE_RESULT_OK);
}
