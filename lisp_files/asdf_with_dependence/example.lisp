(defun test-function (n)
  (mapcar #'print  (ppcre:all-matches-as-strings "a.+?c" "abc cde a cd"))
  (princ n))



