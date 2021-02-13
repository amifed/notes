function ajax_post(url, data) {
  const ajax = new XMLHttpRequest();
  ajax.open("post", url);
  ajax.setRequestHeader("Content-type", "text/plain");

  if (data) ajax.send(data);
  else ajax.send();

  ajax.onreadystatechange = () => {
    if (ajax.readyState === 4 && ajax.status === 200) {
      console.log(ajax.responseText);
    }
  };
}
