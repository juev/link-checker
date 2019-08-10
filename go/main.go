package main

import (
	"fmt"

	"github.com/fatih/color"
	"github.com/gocolly/colly"
	kingpin "gopkg.in/alecthomas/kingpin.v2"
)

var (
	url = kingpin.Arg("url", "URL for checking links from content").Required().String()
)

func main() {
	kingpin.CommandLine.HelpFlag.Short('h')
	kingpin.Parse()

	fmt.Println("URL: " + *url)

	yellow := color.New(color.Bold, color.FgYellow).SprintFunc()
	red := color.New(color.Bold, color.FgRed).SprintFunc()

	c := colly.NewCollector()
	c.Limit(&colly.LimitRule{
		DomainGlob:  "*",
		Parallelism: 10,
	})
	d := colly.NewCollector(
		colly.MaxDepth(1),
		colly.Async(true),
	)
	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
		link := e.Request.AbsoluteURL(e.Attr("href"))
		d.Visit(link)
		d.Wait()
	})
	c.OnError(func(r *colly.Response, err error) {
		fmt.Println("Error:", err)
	})
	d.OnError(func(r *colly.Response, err error) {
		fmt.Println(red(r.StatusCode))
	})
	d.OnResponse(func(r *colly.Response) {
		fmt.Println(yellow(r.StatusCode))
	})
	d.OnRequest(func(r *colly.Request) {
		fmt.Printf("Visiting %s => ", r.URL.String())
	})
	c.Visit(*url)
}
