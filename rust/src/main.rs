extern crate clap;
extern crate env_proxy;
extern crate reqwest;
extern crate select;
extern crate url;

use clap::{App, Arg};
use select::document::Document;
use select::predicate::Name;
use std::process;
use url::Url;

fn main() -> Result<(), std::io::Error> {
    let matches = App::new("Test program")
        .version("0.1")
        .about("Some test rust program")
        .arg(
            Arg::with_name("URL")
                .help("Sets the url to use")
                .required(true)
                .index(1),
        )
        .get_matches();

    let url_str = matches.value_of("URL").unwrap_or_default();

    let url = match Url::parse(url_str) {
        Ok(res) => res,
        Err(_) => {
            println!("URL should be: <scheme>://domain.ext[/path[?query]]");
            process::exit(1);
        }
    };

    let mut client = match reqwest::Client::builder().build() {
        Ok(res) => res,
        Err(_) => {
            println!("Cannot create reqwest::Client");
            process::exit(1);
        }
    };
    match env_proxy::for_url_str(&url).to_string() {
        Some(res) => {
            match Url::parse(&res) {
                Ok(res) => {
                    client = match reqwest::Client::builder()
                        .proxy(reqwest::Proxy::all(res).unwrap())
                        .build()
                    {
                        Ok(res) => res,
                        Err(_) => {
                            println!("Cannot create reqwest::Client");
                            process::exit(1);
                        }
                    };
                }
                Err(_) => {
                    println!("Error during parsing proxy url string");
                    process::exit(1);
                }
            };
        }
        None => (),
    };

    if !get_status(&client, url_str.to_string()).is_success() {
        println!("Cannot get {} content", url_str)
    }

    let resp = match client.get(url_str).send() {
        Ok(res) => res,
        Err(_) => {
            println!("Cannot create reqwest to page");
            process::exit(1);
        }
    };

    Document::from_read(resp)
        .expect("Cannot parse document from page")
        .find(Name("a"))
        .filter_map(|n| n.attr("href"))
        .for_each(|x| {
            println!(
                "{}: {}",
                get_full_url(&url, x.to_string()),
                get_status(&client, x.to_string())
            )
        });
    Ok(())
}

fn get_full_url(base: &Url, url: String) -> String {
    match Url::parse(&url) {
        Ok(_) => return url,
        Err(url::ParseError::RelativeUrlWithoutBase) => {
            return base.join(&url).unwrap().as_str().to_string()
        }
        Err(_) => return "Something wrong".to_string(),
    }
}

fn get_status(client: &reqwest::Client, url: String) -> reqwest::StatusCode {
    client.head(&url).send().unwrap().status()
}
