# link-checker

[![Build Status](https://travis-ci.com/juev/link-checker.svg?branch=master)](https://travis-ci.com/juev/link-checker)

Using libraries: curl

For compiling you need to install libraries (on MacOS):

    % brew install curl

### Example:

    → ./bin/link-checker //ya.ru                                                                                                                                            
    *  https://mail.yandex.ru                                                                                              200
    *  https://yandex.ru                                                                                                   200
    *  https://yandex.ru/blog/company/rss                                                                                  200
    *  https://yandex.ru/company/press_releases/news.rss                                                                   200
    *  https://yandex.ru/opensearch.xml                                                                                    200
    *  https://yastatic.net/iconostasis/_/5mdPq4V7ghRgzBvMkCaTzd2fjYg.png                                                  200
    *  https://yastatic.net/iconostasis/_/8lFaTHLDzmsEZz-5XaQg9iTWZGE.png                                                  200
    *  https://yastatic.net/iconostasis/_/KnU823iWwj_vrPra7x9aQ-4yjRw.png                                                  200
    *  https://yastatic.net/iconostasis/_/s-hGoCQMUosTziuARBks08IUxmc.png                                                  200
    *  https://yastatic.net/iconostasis/_/wT9gfGZZ80sP0VsoR6dgDyXJf2Y.png                                                  200
    *  https://yastatic.net/www/_/g/i/3gXxC6GpD9vzV7LpmvVwiuA1o.css                                                        200
