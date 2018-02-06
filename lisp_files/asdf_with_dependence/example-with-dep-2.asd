(asdf:defsystem #:example-with-dep-2
  :serial t
  :depends-on (#:cl-ppcre)
  :components ((:file "package")
	       (:file "example")))
