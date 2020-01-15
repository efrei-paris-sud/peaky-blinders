from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
import subprocess


import time

hostName = "0.0.0.0"
serverPort = 8080

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        query = urlparse(self.path).query
        query_components = dict(qc.split("=") for qc in query.split("&"))

        outId = query_components["id"]
        outValue = query_components["value"]

        param = int(outId)+64*(1-int(outValue))
        print("Query : %s %s %s" % (outId, outValue, param))
        subprocess.run(["/usr/sbin/i2cget", "-y", "1", "0x10", str(param)])
        self.wfile.write(bytes("ok", "utf-8"))

if __name__ == "__main__":
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
